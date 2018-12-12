//
// Created by lixin on 18-12-10.
//

//#include <shared_ptr.h>

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "common.hpp"

namespace PLXSLAM
{
    class Camera
    {
    public:
        typedef std::shared_ptr<Camera> Ptr;
        float fx_, fy_,cx_, cy_, depth_scale_;  // Camera intrinsics

        Camera();
        Camera ( float fx, float fy, float cx, float cy, float depth_scale=0 ) :
                fx_ ( fx ), fy_ ( fy ), cx_ ( cx ), cy_ ( cy ), depth_scale_ ( depth_scale )
        {}

        void world2camera(const Point3d &p_w, const Mat &R_c_w, const Mat& t_c_w, Point3d& p_c);
        void camera2world(const Point3d &p_c, const Mat &R_c_w, const Mat& t_c_w, Point3d& p_w);
        //TODO use Mat or pt2d,pt3d?
        void camera2pixel(const Point3d& p_c, Point2f& p_p);
        void pixel2camera(const Point2f &p_p, Point3d& p_c, double depth = 1);
        void pixel2world(const Point2f& p_p, const Mat &R_c_w, const Mat& t_c_w, Point3d& p_w, double depth = 1);
        void world2pixel(const Point3d&p_w, const Mat &R_c_w, const Mat& t_c_w, Point2f& p_p);

    };
}

#endif //CAMERA_HPP