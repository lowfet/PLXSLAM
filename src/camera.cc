//
// Created by lixin on 18-12-10.
//

#include "camera.hpp"
#include "config.hpp"

namespace PLXSLAM
{
    Camera::Camera()
    {
        fx_ = Config::get<float>("camera.fx");
        fy_ = Config::get<float>("camera.fy");
        cx_ = Config::get<float>("camera.cx");
        cy_ = Config::get<float>("camera.cy");
        depth_scale_ = Config::get<float>("camera.depth_scale");
    }
    void Camera::world2camera(const Point3d &p_w, const Mat &R_c_w, const Mat& t_c_w, Point3d& p_c)
    {
        Mat point_cam = R_c_w * Mat(p_w) + t_c_w;
        p_c.x = point_cam.at<double>(0,0);
        p_c.y = point_cam.at<double>(1,0);
        p_c.z = point_cam.at<double>(2,0);
    }
    void Camera::camera2world(const Point3d &p_c, const Mat &R_c_w, const Mat& t_c_w, Point3d& p_w)
    {
        Mat point_world = R_c_w.inv() * Mat(p_c) + t_c_w;
        p_w.x = point_world.at<double>(0,0);
        p_w.y = point_world.at<double>(1,0);
        p_w.z = point_world.at<double>(2,0);

    }
    void Camera::camera2pixel(const Point3d& p_c, Point2f& p_p)
    {
        p_p.x = (float)(fx_ * (p_c.x / p_c.z) + cx_);
        p_p.y = (float)(fy_ * (p_c.y / p_c.z) + cy_);
    }
    void Camera::pixel2camera(const Point2f &p_p, Point3d& p_c, double depth)
    {
        p_c.z = depth;
        p_c.x = ((double)(p_p.x) - cx_) / fx_ * depth;
        p_c.y = ((double)(p_p.y) - cy_) / fy_ * depth;
    }
    void Camera::pixel2world(const Point2f& p_p, const Mat &R_c_w, const Mat& t_c_w, Point3d& p_w, double depth)
    {
        Mat point_cam = (cv::Mat_<double>(3,1) << (double)p_p.x, (double)p_p.y, depth);
        Mat point_world = R_c_w.inv() * point_cam + t_c_w;
        p_w.x = point_world.at<double>(0,0);
        p_w.y = point_world.at<double>(1,0);
        p_w.z = point_world.at<double>(2,0);
    }
    void Camera::world2pixel(const Point3d&p_w, const Mat &R_c_w, const Mat& t_c_w, Point2f& p_p)
    {
        Mat point_cam = R_c_w * Mat(p_w) + t_c_w;
        p_p.x = (float)(point_cam.at<double>(0,0) / point_cam.at<double>(2,0));
        p_p.y = (float)(point_cam.at<double>(1,0) / point_cam.at<double>(2,0));
    }

}