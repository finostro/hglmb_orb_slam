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


#include <iostream>
#include <bitset>
#include <boost/math/distributions/binomial.hpp>
#include <opencv2/core/core.hpp>


namespace rfs{

  class ORBDescriptor
    {
    public:
      std::bitset<256> desc;


      ORBDescriptor(){

      }

      ORBDescriptor(cv::Mat vc_desc){
        for (int i = 0 ;i <4; i++){
          unsigned long long * ulongptr = (unsigned long long *)vc_desc.ptr(0);
          std::bitset<256> tmp(*(ulongptr+i));
        }

      }

      void from_mat(cv::Mat vc_desc){
        desc.reset();
        for (int i = 0 ;i <4; i++){
          unsigned long long * ulongptr = (unsigned long long *)vc_desc.ptr(0);
          std::bitset<256> tmp(*(ulongptr+i));
          desc |= tmp<<(i*64);
        }
        // std::cout << vc_desc << "\n";
        // std::cout << desc << "\n";
      }

      void random(){
        desc =lrand48();
        for(int i=0;i<7;i++){
          desc<<=32;
          desc|=lrand48();
        }

      };

      ORBDescriptor sample(){
        ORBDescriptor  retval,mask;
        mask.random();
        for(int i =0; i<2 ;i++) {
          retval.random();
          mask.desc &= retval.desc;
        }

        retval.desc = desc^mask.desc;
        return retval;
      }

      double likelihood(const ORBDescriptor &left, const ORBDescriptor &right){
        double d = distance(*this, left)+distance(*this, right);
        if (d > 200) return -std::numeric_limits<double>::infinity();
        static  double a = std::log(1.0/8.0);
        static  double b = std::log(7.0/8.0);
        static  double c = std::log(1.0/2.0);
        static constexpr double f = -2.0;
        double ret =d*f;
        //std::cout << d << "\n";
        return  ret;
      }
      double falseAlarmLikelihood(){

        return pow(1/2.0/(1-1/2.10) , 256) * pow(1/1.1,32); //1.0;//
      }

      static size_t distance (const ORBDescriptor &a,const ORBDescriptor &b){
        return ((a.desc^b.desc)).count();
      }

    };




}



