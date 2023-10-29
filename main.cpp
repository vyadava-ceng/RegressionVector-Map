#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>


// cv::Mat Readconfig(std::string filename,std::string name)
// {   
//     cv::FileStorage fs;
//     fs.open( filename, cv::FileStorage::READ );
//     cv::Mat M;
//     cv::FileNode fn;
//     fn = fs["name"];
//     fs["name"] << M;
//     fs.release();
//     std::cout<<M<<std::endl;
//     return M;
// }

// void  writeconfig(std::string filename,std::string tag)
// {   cv::FileStorage fs;
//     fs.open( filename, cv::FileStorage::WRITE);


//     cv::Mat M;
//     fs[ "TransformationMatrix"] >> M;

//     fs.release();
//     std::cout<<M<<std::endl;
    
// }
int main()
{
   std::vector<std::map< double, cv::Mat >> RegressionFront;
   std::string filename = "//home/npd_user/Rajan/RegressionVector-Map/files/82.5/calib/Front_Transformation_Calib.yaml";
   //cv::Mat H = Readconfig(filename,"TransformationMatrix");
   
   cv::FileStorage fs;
   filename = "//home/npd_user/Rajan/RegressionVector-Map/files/82.5/calib/check_Calib.yaml";
   fs.open( filename, cv::FileStorage::WRITE);
   fs<<"Number of samples"<<5;
   fs << "objects"<<"[";
   for (int i = 0; i < 5;i++)
   {
     fs << "{";
     fs <<  "distance" << i;
     fs <<  "matrix" << cv::Mat::eye(3,3,CV_32F);
     fs <<  "matrix1" << cv::Mat::eye(3,3,CV_32F);
     //fs <<  "z" << 3;
     fs << "}";
   }
   fs <<"]";
   fs.release();
   fs.open( filename, cv::FileStorage::READ);
   int nobjects;
   fs["number_of_objects"]>> nobjects;
   cv::FileNode fn = fs["objects"];
   int id = 0;
   for (cv::FileNodeIterator it = fn.begin(); it != fn.end(); it++, id++)
   {
     cv::FileNode item = *it;
     int distance;
     cv::Mat matrix;
     item["distance"]>>distance;
     item["matrix"]>>matrix;
     std::cout<<distance<<"\n"<<matrix;
   }

}
