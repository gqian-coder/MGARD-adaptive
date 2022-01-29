// Copyright 2017, Brown University, Providence, RI.
// MGARD: MultiGrid Adaptive Reduction of Data
// Authors: Mark Ainsworth, Ozan Tugluk, Ben Whitney
// Corresponding Author: Ben Whitney, Qing Liu
//
// See LICENSE for details.
#ifndef COMPRESS_TPP
#define COMPRESS_TPP

#include <cstddef>

#include <algorithm>
#include <array>
#include <numeric>
#include <vector>
#include <numeric>

#include "TensorMultilevelCoefficientQuantizer.hpp"
#include "TensorNorms.hpp"
#include "decompose.hpp"
#include "shuffle.hpp"

namespace mgard {

template <std::size_t N, typename Real>
CompressedDataset<N, Real>::CompressedDataset(
    const TensorMeshHierarchy<N, Real> &hierarchy, const Real s,
    const Real tolerance, void const *const data, const std::size_t size)
    : hierarchy(hierarchy), s(s), tolerance(tolerance),
      data_(static_cast<unsigned char const *>(data)), size_(size) {}

template <std::size_t N, typename Real>
void const *CompressedDataset<N, Real>::data() const {
  return data_.get();
}

template <std::size_t N, typename Real>
std::size_t CompressedDataset<N, Real>::size() const {
  return size_;
}

template <std::size_t N, typename Real>
DecompressedDataset<N, Real>::DecompressedDataset(
    const CompressedDataset<N, Real> &compressed, Real const *const data)
    : hierarchy(compressed.hierarchy), s(compressed.s),
      tolerance(compressed.tolerance), data_(data) {}

template <std::size_t N, typename Real>
Real const *DecompressedDataset<N, Real>::data() const {
  return data_.get();
}

struct box_coord2d {
	size_t x0;
	size_t x1;
	size_t y0;
	size_t y1;
};

struct customized_hierarchy {
	size_t *level;
	size_t L;
	size_t Row;
	size_t Col;
	size_t Height;
	size_t l_th;
};

void get_hist_blc_coord(std::vector<box_coord2d> &blc_set, int nbin_R, int nbin_C, 
						int Row, int Col, size_t bin_w, size_t r0, size_t c0) {	
	int k=0;
	std::vector<size_t> coord_r0(nbin_R);
	std::vector<size_t> coord_r1(nbin_R);
	std::vector<size_t> coord_c0(nbin_C);
	std::vector<size_t> coord_c1(nbin_C);
	for (int r=0; r<nbin_R-1; r++) {
		coord_r0.at(r) = r0+r*bin_w;
        coord_r1.at(r) = coord_r0.at(r) + bin_w; 
	}
	coord_r0.at(nbin_R-1) = r0+(nbin_R-1)*bin_w;
	coord_r1.at(nbin_R-1) = r0+Row;
    if (Col>1) { // 2D
    	for (int c=0; c<nbin_C-1; c++) {
            coord_c0.at(c) = c0+c*bin_w;
            coord_c1.at(c) = coord_c0.at(c) + bin_w;
        }
	    coord_c0.at(nbin_C-1) = c0+(nbin_C-1)*bin_w;
	    coord_c1.at(nbin_C-1) = c0+Col;
    } else { // 1D
        std::fill(coord_c0.begin(), coord_c0.end(), 0);
        std::fill(coord_c1.begin(), coord_c1.end(), 1);
    }
    
	for(int r=0; r<nbin_R; r++) {
		for (int c=0; c<nbin_C; c++) {
			blc_set.at(k).x0 = coord_r0.at(r); 
			blc_set.at(k).x1 = coord_r1.at(r);
            blc_set.at(k).y0 = coord_c0.at(c);
            blc_set.at(k).y1 = coord_c1.at(c);
			k++;
		}
	}
}

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values
  std::stable_sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

  return idx;
}

#define KAI 0.08
#define Alpha 1.414

template <typename Real>
struct box_coord2d expand_boundary(struct box_coord2d coord, const Real* u_mc, size_t nb_w, Real nb_thresh, 
									customized_hierarchy &c_hierarchy) {
    size_t Row = c_hierarchy.Row;
    size_t Col = c_hierarchy.Col;
	struct box_coord2d child_blc = {coord.x0, coord.x1, coord.y0, coord.y1};
	int temp = coord.x0 - nb_w;
	size_t ext_r0 = (temp>0) ? temp : 0; 
	temp = coord.x1 + nb_w;
	size_t ext_r1 = (temp<Row) ? temp : Row;
	temp = coord.y0 - nb_w;
	size_t ext_c0 = (temp>0) ? temp : 0;
	temp = coord.y1 + nb_w;
	size_t ext_c1 = (temp<Col) ? temp : Col;
	Real nbw_top=0, nbw_bottom=0, nbw_left=0, nbw_right=0;
//	std::cout << "ext_r0=" << ext_r0 << ", ext_r1=" << ext_r1 << ", ext_c0=" << ext_c0 << ", ext_c1=" << ext_c1 << "\n";
//	std::cout << "{" << coord.x0 << ", " << coord.x1 << ", " << coord.y0 << ", " << coord.y1 << "}\n";
    size_t l;
	for (int r=ext_r0; r<ext_r1; r++) {
		int r0 = r*Col;
		if (r<coord.x0) { 
			for (int c=r0+coord.y0; c<r0+coord.y1; c++){
                l = c_hierarchy.level[c];
				nbw_top += std::abs(u_mc[c]) / std::pow(Alpha, c_hierarchy.L-l);
			}
		} else if ((r>=coord.x0) && (r<coord.x1)) {
			for (int c=r0+ext_c0; c<r0+coord.y0; c++) {
                l = c_hierarchy.level[c];
				nbw_left  += std::abs(u_mc[c]) / std::pow(Alpha, c_hierarchy.L-l);
			}
			for (int c=r0+coord.y1; c<r0+ext_c1; c++) {
                l = c_hierarchy.level[c];
				nbw_right += std::abs(u_mc[c]) / std::pow(Alpha, c_hierarchy.L-l);
			}
		} else {
			for (int c=r0+coord.y0; c<r0+coord.y1; c++) {
                l = c_hierarchy.level[c];
				nbw_bottom += std::abs(u_mc[c]) / std::pow(Alpha, c_hierarchy.L-l);
			}
		}
	}
	if (nbw_top >= nb_thresh) {
		child_blc.x0 = ext_r0;
	}
	if (nbw_bottom >= nb_thresh) {
		child_blc.x1 = ext_r1;
	}
	if (nbw_left >= nb_thresh) {
		child_blc.y0 = ext_c0;
	}
	if (nbw_right >= nb_thresh) {
		child_blc.y1 = ext_c1;
	}
//	std::cout << "child_blc: {" << child_blc.x0 << ", " << child_blc.x1 << ", " << child_blc.y0 << ", " << child_blc.y1 << "}\n";
	return child_blc;
}

// return the id of blocks whose coefficients sum are large and expand the block boundary
template <typename Real>
std::vector<struct box_coord2d> filter_hist_blc(const Real *u_mc, customized_hierarchy &c_hierarchy, std::vector<box_coord2d> &blc_set, const Real thresh, size_t bin_w) {
	size_t nbins = blc_set.size();
//	std::cout << "number of bins: " << nbins << "\n";
	std::vector<Real>hist_w (nbins, 0);	
	for (int i=0; i<nbins; i++) {
		for (int r=blc_set.at(i).x0; r<blc_set.at(i).x1; r++) {
			int r0 = r*c_hierarchy.Col;
			for (int c=blc_set.at(i).y0; c<blc_set.at(i).y1; c++) {
				size_t l = c_hierarchy.level[r0+c];
				hist_w[i] += std::abs(u_mc[r0+c]) / std::pow(Alpha, c_hierarchy.L-l);
			}
		}
		Real area = (blc_set.at(i).x1 - blc_set.at(i).x0) * (blc_set.at(i).y1 - blc_set.at(i).y0);
		hist_w[i] = hist_w[i] / area;
	}
	std::vector<size_t> sid_umc = sort_indexes(hist_w);
//	for (int i=0; i<nbins; i++) {
//		std::cout << "u_mc[" << sid_umc[i] << "] = " << hist_w[sid_umc[i]] << "\n";
//	}
	int n_filtered = (int)std::ceil(thresh*nbins);
	std::vector<struct box_coord2d> filtered_set(n_filtered);	
	// expand the boundary by KAI
	size_t nb_w = (size_t)(std::ceil((float)bin_w * KAI));
	float edge_ratio = (float)nb_w / (float)bin_w;
//	std::cout << "bin_w = " << bin_w << ", edge ratio: " << edge_ratio << "\n";
	for (int i=0; i<n_filtered; i++) {
		if (bin_w > 1) {
			Real nb_thresh = edge_ratio*hist_w.at(sid_umc.at(i));
			filtered_set.at(i) = expand_boundary<Real>(blc_set.at(sid_umc.at(i)), u_mc, nb_w, nb_thresh, c_hierarchy);
		} else {
			filtered_set.at(i) = blc_set.at(sid_umc.at(i));
		}
	}
	return filtered_set;
}


template <typename Real>
void check_nearby_lgc(const Real *u_mc, customized_hierarchy &c_hierarchy, Real *u_map, 
						int r, int c, const size_t rad, std::vector<size_t> R2, u_char flag)
{
  int k;
  std::vector<int> top_r{0, 0, r, r}; 
  std::vector<int> bottom_r{r, r, c_hierarchy.Row, c_hierarchy.Row};
  std::vector<int> left_c{0, c, 0, c};
  std::vector<int> right_c{c, c_hierarchy.Col, c, c_hierarchy.Col};
  size_t l, backoff_dist;
  int temp = r-rad;
  if (temp>0) {top_r[0] = temp; top_r[1] = temp;} 
  temp = c-rad;
  if (temp>0) {left_c[0] = temp; left_c[2] = temp;}
  temp = r+rad+1;
  if (temp<c_hierarchy.Row) {bottom_r[2] = temp; bottom_r[3] = temp;}
  temp = c+rad+1;
  if (temp<c_hierarchy.Col) {right_c[1] = temp; right_c[3] = temp;}
  size_t l_th = c_hierarchy.l_th;
  size_t Col  = c_hierarchy.Col;
  for (int fg=0; fg<4; fg++) { // top left, top right, bottom left, bottom right
    if ((flag & (1<<fg))) { 
      for (int rr=top_r[fg]; rr<bottom_r[fg]; rr++) {
        for (int cc=left_c[fg]; cc<right_c[fg]; cc++) {
          k = rr*Col+cc;
          if (u_map[k]!=0) {
            l = c_hierarchy.level[k];
            if (l>=l_th) {
              backoff_dist = ((rr==r) || (cc==c)) ? 0.75*R2[l-l_th] : R2[l-l_th];
              if (std::abs(rr-r)+std::abs(cc-c) < backoff_dist) {
                u_map[k] = 0;
              }
            }
          }
        }
      }
    } 
  }
}

template <typename Real>
void check_edge_coeff(const Real *u_mc, customized_hierarchy &c_hierarchy, Real *u_map,
                        int rleft, int rright, int cleft, int cright, int max_rad,
                        std::vector<size_t> R2)
{
    std::vector<int>rr_vec{rleft, rright};
    std::vector<int>cc_vec{cleft, cright};
    std::vector<u_char>flag{3, 12, 5, 10};
    int cnt=0;
    // the top and bottom horizontal edge 
    for (std::vector<int>::iterator rr = rr_vec.begin() ; rr != rr_vec.end(); ++rr) {
        int r00 = (*rr)*c_hierarchy.Col;
        for (int cc=cleft; cc<cright+1; cc++) {
            check_nearby_lgc<Real>(u_mc, c_hierarchy, u_map, (*rr), cc, max_rad, R2, flag[cnt]);
        }
        cnt ++;
    }
    // the left and right vertical edge
    for (std::vector<int>::iterator cc = cc_vec.begin() ; cc != cc_vec.end(); ++cc) {
        for (int rr=rleft+1; rr<rright; rr++) {
            int r00 = rr*c_hierarchy.Col;
            check_nearby_lgc<Real>(u_mc, c_hierarchy, u_map, rr, (*cc), max_rad, R2, flag[cnt]);
        }
        cnt ++;
    }
}

//double avg_rad = 0;
//int    cnt_pts = 0;

template <typename Real>
void dfs_amr(std::vector<struct box_coord2d> blc_set, const Real *u_mc, customized_hierarchy &c_hierarchy, 
			const std::vector<Real> thresh, int &depth, size_t &bin_w, const size_t bin_min, 
            const std::vector<size_t> ratio_bin, Real* u_map, const size_t max_rad, const std::vector<size_t> R2) {
//	std::cout << "initial bin_w = " << bin_w << ", ratio_R = " << ratio_bin[depth] << "\n";
	bin_w = std::ceil(bin_w / ratio_bin[depth]);
//	std::cout << "depth = " << depth << ", bin_w = " << bin_w << "\n";
//	std::cout << "number of bins: " << blc_set.size() << "\n";
	for (int k=0; k<blc_set.size(); k++) {
		size_t bR  = blc_set.at(k).x1 - blc_set.at(k).x0;
		size_t bC  = blc_set.at(k).y1 - blc_set.at(k).y0;
		size_t nbin_R = (size_t)std::ceil((float)bR / bin_w);
		size_t nbin_C = (size_t)std::ceil((float)bC / bin_w);
//		std::cout << "{" <<  blc_set.at(k).x0 << ", " <<  blc_set.at(k).x1 << ", " <<  blc_set.at(k).y0 << ", " <<  blc_set.at(k).y1 << "}\n";
//		std::cout << "k = " << k << ", bR = " << bR << ", bC = " << bC << ", nbin_R = " << nbin_R << ", nbin_C = " << nbin_C << "\n";
		std::vector<struct box_coord2d> child_set(nbin_R*nbin_C);
		get_hist_blc_coord(child_set, nbin_R, nbin_C, bR, bC, bin_w, blc_set.at(k).x0, blc_set.at(k).y0);
		std::vector<struct box_coord2d>filtered_set = filter_hist_blc<Real>(u_mc, c_hierarchy, child_set, thresh[depth], bin_w);
		if (bin_w <= bin_min){
//            std::cout << "max_rad: " << max_rad << "\n";
			for (int cid=0; cid<filtered_set.size(); cid++) {
                int r, c;
				for (r=filtered_set.at(cid).x0; r<filtered_set.at(cid).x1; r++) {
					int r0 = r * c_hierarchy.Col;
					for (c=filtered_set.at(cid).y0; c<filtered_set.at(cid).y1; c++) {
						// to avoid the impact from neighboring coefficients at coarser level
						// check_nearby_lgc
//						std::cout << "cid = " << cid << ", r = " << r << ", c = " << c << "\n";
					    const std::size_t l = c_hierarchy.level[r0+c];
						if (l >= c_hierarchy.l_th) {
							int rad = static_cast<int>(1<<(c_hierarchy.L - l));
							int rleft  = (r-rad > 0) ? (r-rad) : 0;
							int rright = (r+rad+1<c_hierarchy.Row) ? (r+rad+1) : c_hierarchy.Row;
                            int cleft  = (c-rad>0) ? c-rad : 0;
                            int cright = (c+rad+1<c_hierarchy.Col) ? (c+rad+1) : c_hierarchy.Col;
							for (int rr=rleft; rr<rright; rr++) {
								int r00 = rr*c_hierarchy.Col;
   	                			for (int cc=cleft; cc<cright; cc++) {
//                                    check_nearby_lgc<Real>(u_mc, c_hierarchy, u_map, rr, cc, max_rad, R2);
									u_map[r00+cc] = 0;
								}
							}
						}
					}
				}
                // only check the edge of each histogram bin 
                std::vector<int> row_vec {filtered_set.at(cid).x0};
                if (filtered_set.at(cid).x1 - filtered_set.at(cid).x0 > 1) {
                    row_vec.push_back(filtered_set.at(cid).x1-1);
                }
                for (std::vector<int>::iterator it = row_vec.begin() ; it != row_vec.end(); ++it) { 
                    r = (*it);
                    int r0 = r * c_hierarchy.Col;
                    for (c=filtered_set.at(cid).y0; c<filtered_set.at(cid).y1; c++) {
                        // check
                        const std::size_t l = c_hierarchy.level[r0+c];
                        if (l >= c_hierarchy.l_th) { 
                            int rad = static_cast<int>(1<<(c_hierarchy.L - l));
//                            avg_rad += (double)rad;
//                            cnt_pts ++;
                            int rleft  = (r-rad > 0) ? (r-rad) : 0;
                            int rright = (r+rad<c_hierarchy.Row) ? (r+rad) : c_hierarchy.Row-1;
                            int cleft  = (c-rad>0) ? c-rad : 0;
                            int cright = (c+rad<c_hierarchy.Col) ? (c+rad) : c_hierarchy.Col-1;
                            check_edge_coeff(u_mc, c_hierarchy, u_map, rleft, rright, cleft, cright, max_rad, R2);
                        }
                    }
                }
                if ((c_hierarchy.Col > 1) && (bin_w>1)) {
                    std::vector<int> col_vec {filtered_set.at(cid).y0};
                    if (filtered_set.at(cid).y1 - filtered_set.at(cid).y0 > 1) {
                        col_vec.push_back(filtered_set.at(cid).y1-1);
                    }
                    for (std::vector<int>::iterator it = col_vec.begin() ; it != col_vec.end(); ++it) {
                        c = (*it);
                        for (int r=filtered_set.at(cid).x0+1; r<filtered_set.at(cid).x1; r++) {
                        // check
                            int r0 = r * c_hierarchy.Col;
                            const std::size_t l = c_hierarchy.level[r0+c];
                            if (l >= c_hierarchy.l_th) {
                                int rad = static_cast<int>(1<<(c_hierarchy.L - l));
                                int rleft  = (r-rad > 0) ? (r-rad) : 0;
                                int rright = (r+rad<c_hierarchy.Row) ? (r+rad) : c_hierarchy.Row-1;
                                int cleft  = (c-rad>0) ? c-rad : 0;
                                int cright = (c+rad<c_hierarchy.Col) ? (c+rad) : c_hierarchy.Col-1;
                                check_edge_coeff(u_mc, c_hierarchy, u_map, rleft, rright, cleft, cright, max_rad, R2);
                            }
                        }
                    }
                }
			}
		} else {
//			std::cout << "call recursive dfs_arm, depth = " << depth << ", bin_w = " << bin_w << ", # of blocks: " << filtered_set.size() << " / " << child_set.size() << "\n";
			depth ++;
			dfs_amr<Real>(filtered_set, u_mc, c_hierarchy, thresh, depth, bin_w, bin_min, ratio_bin, u_map, max_rad, R2);
		}
	}
	bin_w = size_t(bin_w * ratio_bin[depth]);
	depth --;
}

// u_map: multi-resolution
// k: alpha^(k-1) * least_eb
using DEFAULT_INT_T = long int;
template <std::size_t N, typename Real>
CompressedDataset<N, Real>
compress(const TensorMeshHierarchy<N, Real> &hierarchy, Real *const v, const Real s, 
		const Real tolerance, const std::vector<Real> thresh, 
		 const size_t bin_max, const std::vector<size_t> ratio_bin, const size_t l_th,
        const char* filename, bool wr /*1 for write 0 for read*/) {
  const std::size_t ndof = hierarchy.ndof();
  // TODO: Can be smarter about copies later.
  Real *const u = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  shuffle(hierarchy, v, u);
  decompose(hierarchy, u);
  // create a map for adaptive compression 
  Real *const unshuffled_u = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  unshuffle(hierarchy, u, unshuffled_u);
  const std::array<std::size_t, N> &SHAPE = hierarchy.shapes.back();
  Real* u_map = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  
  if ((wr==0) && (filename!=NULL)) {
    FILE *file = fopen(filename, "rb");
    fread(u_map, sizeof(Real), ndof, file);
  } else {
    int depth = 1;
    size_t bin_w = bin_max;
    size_t bin_min = bin_max;
    for (int i=0; i<ratio_bin.size(); i++) {
        bin_min = (size_t)std::ceil(bin_min / ratio_bin.at(i));
    }
    //  std::memset(u_map, 0, ndof*sizeof(Real));
    //QG! Assume the array is 2D
    int Dim2=1, r, c, h;
    struct customized_hierarchy c_hierarchy;
    c_hierarchy.level = new size_t[ndof];
    c_hierarchy.L     = hierarchy.L;
    c_hierarchy.Row  = (int)SHAPE[0];
    if (N>=2) {
	    c_hierarchy.Col = (int)SHAPE[1];
    } else {
  	    c_hierarchy.Col  = 1;
        c_hierarchy.Height = 1;
    }
    if (N==3) {
  	    c_hierarchy.Height = (int)SHAPE[2];
	    Dim2 = c_hierarchy.Height * c_hierarchy.Col;
    } else {
	    c_hierarchy.Height = 1;
    }
    for (std::size_t i=0; i<ndof; i++) {
        std::array<std::size_t, N> multiindex;
	    if (N==1) {
		    multiindex[0] = i;
	    } else if (N==2) {
		    r = int(i/c_hierarchy.Col);
	        c = i - r*c_hierarchy.Col;
		    multiindex[0] = r;
		    multiindex[1] = c;
	    } else {
		    r = (int)(i / Dim2);
		    c = (int)((i - r*Dim2) / c_hierarchy.Height);
		    h = i % c_hierarchy.Height;
		    multiindex[0] = r;
		    multiindex[1] = c;
		    multiindex[2] = h;
	    }
        c_hierarchy.level[i] = hierarchy.date_of_birth(multiindex);
	    if (c_hierarchy.level[i]<l_th) {
		    u_map[i] = 0;
	    } else {
            u_map[i] = 1;//hierarchy.L; 
        }
    }
    c_hierarchy.l_th = l_th;
//    std::cout << "L_max = " << hierarchy.L << "\n";
    if (l_th<hierarchy.L) {
        // number of bins in the 1st layer of histogram
        int nbin_R = (int)std::ceil((float)c_hierarchy.Row / bin_max);
        int nbin_C = (N>=2) ? (int)std::ceil((float)c_hierarchy.Col / bin_max) : 1;
        int nbin_H = (N>=3) ? (int)std::ceil((float)c_hierarchy.Height / bin_max) : 1;
        std::vector<struct box_coord2d> blc_set(nbin_R*nbin_C*nbin_H);
//        std::cout << "nbin_R = " << nbin_R << ", nbin_C = " << nbin_C << ", nbin_H = " << nbin_H << "\n"; 
//        std::cout << "Col = " << c_hierarchy.Col << ", Row = " << c_hierarchy.Row << ", Height = " << c_hierarchy.Height << "\n";
        get_hist_blc_coord(blc_set, nbin_R, nbin_C, c_hierarchy.Row, c_hierarchy.Col, bin_max, 0, 0);
        std::vector<struct box_coord2d>child_set = filter_hist_blc<Real>(unshuffled_u, c_hierarchy, blc_set, thresh[0], bin_max);

        // depth first search for hierachical block refinement 
//        std::cout << "number of blocks after the 1st thresholding: " << child_set.size() << "/" << blc_set.size() <<"\n";
        size_t max_rad = (size_t)(2 * (1<<(c_hierarchy.L - c_hierarchy.l_th+1))); // 3rd peak to the 0th center 
        std::vector<size_t>R2(c_hierarchy.L-c_hierarchy.l_th+1);
        R2.at(0) = max_rad;
//        std::cout << "max_rad = " << max_rad << "\n";
        for (int i=1; i<c_hierarchy.L-c_hierarchy.l_th+1; i++) {
            R2.at(i) = R2.at(i-1) / 2;
//            std::cout << "R2["<<i<<"] = " << R2.at(i) << ", "; 
        }
//        std::cout << "\n"; 
        dfs_amr<Real>(child_set, unshuffled_u, c_hierarchy, thresh, depth, bin_w, bin_min, ratio_bin, u_map, max_rad, R2);
//        std::cout << "average radius = " << avg_rad / (double)cnt_pts << "\n";
    }
    if (filename != NULL) {
        FILE *fp = fopen (filename, "wb");
        fwrite (u_map , sizeof(Real), ndof, fp);
        fclose(fp);
    }
//    FILE *fp = fopen ("level.bin", "wb");
//    fwrite (c_hierarchy.level , sizeof(size_t), ndof, fp);
//    fclose(fp);
/*    
    size_t nonzr_ = 0;
    for (int i=0; i<ndof; i++) {
        if (u_map[i]==0) {
            nonzr_ ++;
        }
    }
    std::cout << "percentage of high-res in u_map: " << (float)nonzr_*100.0 / ndof << "%\n";
*/
  }

  shuffle(hierarchy, u_map, unshuffled_u);
  // 2D case is bounded by the horizontal direction of coefficient_nodal error propagation  
  // 3rd peak, scalar=125 for 2D if nodal nodal and scalar=50 if nodal coefficient vertical
//  size_t scalar = (N==1)? 30 : ((N==2) ? 50 : 1);   
//  2nd peak, scalar = 33 for 2D if nodal nodal and scalar=13 if nodal coefficient vertical
  size_t scalar = (N==1) ? 8 : ((N==2) ? 33 : 1);  
  // now unshuffled_u is the shuffled u_map
  using Qntzr = TensorMultilevelCoefficientQuantizer<N, Real, DEFAULT_INT_T>;
  const Qntzr quantizer(hierarchy, s, tolerance, scalar);
//  std::cout << "tolerance -- hr: " << tolerance << ", lr: " << tolerance * scalar<< "\n";
  using It = typename Qntzr::iterator;
  const RangeSlice<It> quantized_range = quantizer(u, unshuffled_u);
  const std::vector<DEFAULT_INT_T> quantized(quantized_range.begin(),
                                             quantized_range.end());
  free(u);
  free(unshuffled_u);
  free(u_map);

#ifndef MGARD_ZSTD
  std::vector<std::uint8_t> z_output;
  // TODO: Check whether `compress_memory_z` changes its input.
  compress_memory_z(
      const_cast<void *>(static_cast<void const *>(quantized.data())),
      sizeof(DEFAULT_INT_T) * hierarchy.ndof(), z_output);
  // Possibly we should check that `sizeof(std::uint8_t)` is `1`.
  const std::size_t size = z_output.size();

  void *const buffer = new unsigned char[size];
  std::copy(z_output.begin(), z_output.end(),
            static_cast<unsigned char *>(buffer));
#else
  // Compress an array of data using `zstd`.
  std::size_t size;
  void *const buffer = compress_memory_huffman(quantized, size);
#endif
  return CompressedDataset<N, Real>(hierarchy, s, tolerance, buffer, size);
}


/*
// set error bound by location
template <std::size_t N, typename Real>
CompressedDataset<N, Real>
compress(const TensorMeshHierarchy<N, Real> &hierarchy, Real *const v,
         const Real s, const Real tolerance, const Real thresh, const Real scalar, const Real radius) {
  const std::size_t ndof = hierarchy.ndof();
  // TODO: Can be smarter about copies later.
  Real *const u = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  shuffle(hierarchy, v, u);
  decompose(hierarchy, u);
  // create a map for adaptive compression
  Real *const unshuffled_u = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  Real *const u_map = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  for (size_t i=0; i<ndof; i++) {
  	u_map[i] = 1;	
  }
  u_map[int(thresh)] = 0;

//  std::cout << "max level: " << hierarchy.L << "\n";
//  char map_f[256];
//  sprintf(map_f, "u_map_t%d.bin", (int)radius);
//  FILE *fp = fopen (map_f, "wb");
//  fwrite (u_map , sizeof(Real), ndof, fp);
//  fclose(fp);
  shuffle(hierarchy, u_map, unshuffled_u);
  // now unshuffled_u is the shuffled u_map
  using Qntzr = TensorMultilevelCoefficientQuantizer<N, Real, DEFAULT_INT_T>;
  const Qntzr quantizer(hierarchy, s, tolerance, scalar);
  using It = typename Qntzr::iterator;
  const RangeSlice<It> quantized_range = quantizer(u, unshuffled_u);
  const std::vector<DEFAULT_INT_T> quantized(quantized_range.begin(),
                                             quantized_range.end());
  std::free(u);
  std::free(unshuffled_u);
  std::free(u_map);
//  fp = fopen("quantized_coeff.bin", "wb");
  float *const unshuffled_qc = (float *)std::malloc(ndof * sizeof(float));
  float *const shuffled_qc   = (float *)std::malloc(ndof * sizeof(float));
  for (int i=0; i<ndof; i++) {
      shuffled_qc[i] = (float)quantized.data()[i];
  }
  unshuffle(hierarchy, shuffled_qc, unshuffled_qc);
//  fwrite(unshuffled_qc, sizeof(float), ndof, fp);
//  fclose(fp);
  free(unshuffled_qc);
  free(shuffled_qc);
#ifndef MGARD_ZSTD
  std::vector<std::uint8_t> z_output;
  // TODO: Check whether `compress_memory_z` changes its input.
  compress_memory_z(
      const_cast<void *>(static_cast<void const *>(quantized.data())),
      sizeof(DEFAULT_INT_T) * hierarchy.ndof(), z_output);
  // Possibly we should check that `sizeof(std::uint8_t)` is `1`.
  const std::size_t size = z_output.size();

  void *const buffer = new unsigned char[size];
  std::copy(z_output.begin(), z_output.end(),
            static_cast<unsigned char *>(buffer));
#else
  // Compress an array of data using `zstd`.
  std::size_t size;
  void *const buffer = compress_memory_huffman(quantized, size);
#endif
  return CompressedDataset<N, Real>(hierarchy, s, tolerance, buffer, size);
}
*/

template <std::size_t N, typename Real>
DecompressedDataset<N, Real>
decompress(const CompressedDataset<N, Real> &compressed) {
  const std::size_t ndof = compressed.hierarchy.ndof();
  DEFAULT_INT_T *const quantized =
      static_cast<DEFAULT_INT_T *>(std::malloc(ndof * sizeof(*quantized)));
  // TODO: Figure out all these casts here and above.
#ifndef MGARD_ZSTD
  decompress_memory_z(const_cast<void *>(compressed.data()), compressed.size(),
                      reinterpret_cast<int *>(quantized),
                      ndof * sizeof(*quantized));
#else
  decompress_memory_huffman(
      reinterpret_cast<unsigned char *>(const_cast<void *>(compressed.data())),
      compressed.size(), quantized, ndof * sizeof(*quantized));
#endif
  using Dqntzr = TensorMultilevelCoefficientDequantizer<N, DEFAULT_INT_T, Real>;
  const Dqntzr dequantizer(compressed.hierarchy, compressed.s,
                           compressed.tolerance);
  using It = typename Dqntzr::template iterator<DEFAULT_INT_T *>;
  const RangeSlice<It> dequantized_range =
      dequantizer(quantized, quantized + ndof);

  // TODO: Can be smarter about copies later.
  Real *const buffer = static_cast<Real *>(std::malloc(ndof * sizeof(Real)));
  std::copy(dequantized_range.begin(), dequantized_range.end(), buffer);
  std::free(quantized);

  recompose(compressed.hierarchy, buffer);
  Real *const v = new Real[ndof];
  unshuffle(compressed.hierarchy, buffer, v);
  std::free(buffer);
  return DecompressedDataset<N, Real>(compressed, v);
}

} // namespace mgard

#endif
