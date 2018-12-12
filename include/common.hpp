//
// Created by lixin on 18-12-10.
//

#ifndef PLXSLAM_COMMON_HPP
#define PLXSLAM_COMMON_HPP


// define the commonly included file to avoid a long include list
// for Eigen
//#include <Eigen/Core>
//#include <Eigen/Geometry>
//using Eigen::Vector2d;
//using Eigen::Vector3d;

// for Sophus
//#include <sophus/se3.h>
//using Sophus::SE3;

// for cv
#include <opencv2/core/core.hpp>
using cv::Mat;
using cv::Point2f;
using cv::Point3d;

// std
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <iostream>
#include <set>
#include <unordered_map>
#include <map>

using namespace std;


#endif //PLXSLAM_COMMON_HPP
