#ifndef DEFINES_H
#define DEFINES_H


#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

typedef Eigen::Vector2d Vec2;
typedef Eigen::Vector3d Vec3;
typedef Eigen::Vector3i Vec2i;
typedef Eigen::Vector3i Vec3i;
typedef Eigen::VectorXd Vecd;
typedef Eigen::MatrixXd Matd;


namespace Math {
    template<typename T> int signum(T val) {
        return (T(0) < val) - (val < T(0));
    }

    inline double toRad(double a) {
        return a*M_PI/180.0;
    }

    inline double toDeg(double a) {
        return a*180.0/M_PI;
    }
}


#endif // DEFINES_H
