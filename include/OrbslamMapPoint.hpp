/*
 * Software License Agreement (New BSD License)
 *
 * Copyright (c) 2013, Keith Leung, Felipe Inostroza
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Advanced Mining Technology Center (AMTC), the
 *       Universidad de Chile, nor the names of its contributors may be
 *       used to endorse or promote products derived from this software without
 *       specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AMTC, UNIVERSIDAD DE CHILE, OR THE COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */




#pragma once


#include "g2o/types/sba/types_six_dof_expmap.h" // se3 poses
#include <opencv2/core/core.hpp>
#include <ORB.hpp>

namespace rfs
{
	class OrbslamPose;




    class OrbslamMapPoint
    {

    public:
        typedef g2o::VertexSBAPointXYZ PointType;
        typedef g2o::VertexSE3Expmap PoseType;
        typedef g2o::EdgeProjectXYZ2UV MonocularMeasurementEdge;
        typedef g2o::EdgeStereoSE3ProjectXYZ StereoMeasurementEdge;


        PointType *pPoint;
        int numDetections_;
        int numFoV_;
        int id;
        double birthTime_;
        // creation
        int  birthMatch;
        OrbslamPose *birthPose;

        std::vector<int> is_in_fov_;

        // Mean viewing direction
        Eigen::Vector3d normalVector;

        // Best descriptor to fast matching
        ORBDescriptor descriptor;

        // Scale invariance distances
        float mfMinDistance;
        float mfMaxDistance;

        //hessian 
        Eigen::Matrix<double, PointType::Dimension,	  PointType::Dimension> hessian;


        int predictScale(double dist, OrbslamPose *pPose);

        





    };

}
