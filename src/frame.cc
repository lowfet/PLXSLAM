//
// Created by lixin on 18-12-10.
//

#include "frame.hpp"

namespace PLXSLAM
{
    Frame::Frame()
            : id_(-1), time_stamp_(-1), camera_(nullptr), is_key_frame_(false)
    {

    }

    Frame::Frame ( long id, double time_stamp, Mat R_c_w, Mat t_c_w, Camera::Ptr camera, Mat color)
            : id_(id), time_stamp_(time_stamp), R_c_w_(R_c_w), t_c_w_(t_c_w), camera_(camera), color_(color),is_key_frame_(false)
    {

    }

    Frame::~Frame()
    {

    }

    Frame::Ptr Frame::createFrame()
    {
        static long factory_id = 0;
        return Frame::Ptr( new Frame(factory_id++) );
    }

    bool Frame::isInFrame ( const Point3d& pt_world )
    {
        Point3d p_cam ;
        camera_->world2camera( pt_world, R_c_w_, t_c_w_, p_cam);
        // cout<<"P_camera = "<< p_cam <<endl;
        if ( p_cam.z < 0 ) return false;
        Point2f p_p;
        camera_->world2pixel( pt_world, R_c_w_, t_c_w_, p_p);
        // cout<<"P_pixel = "<< p_p <<endl<<endl;
        return  p_p.x > 0 &&
                p_p.y > 0 &&
                p_p.x < color_.cols &&
                p_p.y < color_.rows;
    }

    Mat Frame::getCamCenter() const
    {
        //TODO not comfrim is t_c_w or -t_c_w
        return t_c_w_;
    }

    void Frame::setPose ( const Mat& R_c_w , const Mat& t_c_w )
    {
        R_c_w_ = R_c_w;
        t_c_w_ = t_c_w;
    }


    double Frame::findDepth ( const cv::KeyPoint& kp )
    {
        int x = cvRound(kp.pt.x);
        int y = cvRound(kp.pt.y);
        ushort d = depth_.ptr<ushort>(y)[x];
        if ( d!=0 )
        {
            return double(d)/camera_->depth_scale_;
        }
        else
        {
            // check the nearby points
            int dx[4] = {-1,0,1,0};
            int dy[4] = {0,-1,0,1};
            for ( int i=0; i<4; i++ )
            {
                d = depth_.ptr<ushort>( y+dy[i] )[x+dx[i]];
                if ( d!=0 )
                {
                    return double(d)/camera_->depth_scale_;
                }
            }
        }
        return -1.0;
    }
}