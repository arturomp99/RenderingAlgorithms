#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "defines.h"
#include <QMatrix4x4>
#include <glm/gtc/matrix_transform.hpp>

class Camera {

public:
    Camera();
    ~Camera();

    /**
     * @brief SetViewport Calls glViewport with the current viewport position,
     * width and height and stores these values.
     * @param x Viewport position x.
     * @param y Viewport position y.
     * @param w Viewport width-
     * @param h Viewport height.
     */
    void setViewport(int x, int y, int w, int h);
    void setViewport() const;

    /**
     * @brief SetModel Returns a model transform matrix that centers the last
     * "updated" model and scales its bounding box longest edge to unit length.
     * @return A modeling transform.
     */
    Eigen::Matrix4f SetModel() const;

    Eigen::Matrix4f SetView() const; // Returns the viewing matrix

    Eigen::Matrix4f SetProjection(double fov, double znear, double zfar);   // Computes the projection matrix
    Eigen::Matrix4f SetProjection() const;

    Eigen::Matrix4f SetIdentity() const; // Returns an identity matrix

    void Zoom(double modifier); // It zooms the camera in the direction given by the modifier
    void SafeZoom(double modifier); // zooms if zooming is active
    void SafePan(double x, double y);   // pans the camera by the displaced mouse position
    void Rotate(double modifier);   // Rotates the camera around the Y axis. modifier is the sign of the rotation direction
    void SetRotationX(double y);    // If rotating is active, rotates the camera around the X axis.
    void SetRotationY(double x);    // If rotating is active, rotates the camera around the Y axis.

    void StartRotating(double x, double y); // Allows camera rotation with starting mouse position (x,y).
    void StopRotating(double x, double y);  // StopRotating Finishes camera rotation with ending mouse position (x,y).
    void StartZooming(double x, double y);
    void StopZooming(double x, double y);
    void StartPanning(double x, double y);
    void StopPanning(double x, double y);

    /**
     * @brief UpdateModel Updates the intrinsic parameters to compute a modeling
     * transform that centers the bounding box of the model and makes its longest
     * edge unit length.
     * @param min Minimum point of the model bounding box.
     * @param max Maximum point of the model bounding box.
     */
    void UpdateModel(Eigen::Vector3f min, Eigen::Vector3f max);

    void SetCameraStep(double step);

private:
    double distance_;   // Zoom distance
    double step_;   //determines the influence of the mouse movement over the camera.
    bool rotating_, zooming_, panning_;

    double rotationY_, rotationX_; // Camera rotation around the Y and X axes, respecively.
    double panX_, panY_;
    double currentX_, currentY_; // Stores the mouse's current position to compute displacements.
    double viewportX_, viewportY_;
    int viewportWidth_, viewportHeight_;
    double centeringX_, centeringY_, centeringZ_; // Translation applied to the modeling transform. Tries to center a model bounding box.
    double scaling_; //Scaling applied to the modeling transform. Tries to make unit length the longest edge of a model bounding box.
    double fov_, zNear_, zFar_;

    const Eigen::Vector3f vra, hra;

    const double kMaxCameraDistance = 3.0;
    const double kMinCameraDistance = -kMaxCameraDistance;

    const double kMinRotationX = -M_PI / 2;
    const double MaxRotationX = M_PI / 2;

    const double AngleIncrement = 0.01;
};

#endif // CAMERA_H
