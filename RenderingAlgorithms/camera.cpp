#include "camera.h"

Camera::Camera() :
    distance_(2.0),
    step_(0.05),
    rotating_(false),
    zooming_(false),
    panning_(false),
    rotationY_(0.0),
    rotationX_(0.0),
    panX_(0.0),
    panY_(0.0),
    currentX_(-1.0),
    currentY_(-1.0),
    viewportX_(0.0),
    viewportY_(0.0),
    viewportWidth_(0.0),
    viewportHeight_(0.0),
    centeringX_(0.0),
    centeringY_(0.0),
    centeringZ_(0.0),
    scaling_(1.0),
    fov_(0.0),
    zNear_(0.0),
    zFar_(0.0),
    vra(0.0,1.0,0.0),
    hra(1.0,0.0,0.0) {}

Camera::~Camera() {}

void Camera::setViewport(int x, int y, int w, int h) {
    viewportX_ = x;
    viewportY_ = y;
    viewportWidth_ = w;
    viewportHeight_ = h;

    glViewport(viewportX_, viewportY_, viewportWidth_, viewportHeight_);
}

void Camera::setViewport() const {
    glViewport(viewportX_, viewportY_, viewportWidth_, viewportHeight_);
}

Eigen::Matrix4f Camera::SetIdentity() const {
  Eigen::Matrix4f identity;
  identity << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1;
  return identity;
}

Eigen::Matrix4f Camera::SetModel() const {
  const Eigen::Affine3f kScaling(Eigen::Scaling(
      Eigen::Vector3d(scaling_, scaling_, scaling_).cast<float>()));
  const Eigen::Affine3f kTranslation(Eigen::Translation3f(
      Eigen::Vector3d(centeringX_, centeringY_, centeringZ_).cast<float>()));
  return kScaling.matrix() * kTranslation.matrix();
}

Eigen::Matrix4f Camera::SetView() const {
    const Eigen::Affine3f kTranslation(Eigen::Translation3f(
        Eigen::Vector3d(panX_, panY_, -distance_).cast<float>()));
    const Eigen::Affine3f kRotationA(
        Eigen::AngleAxisf(static_cast<float>(rotationX_), hra));
    const Eigen::Affine3f kRotationB(
        Eigen::AngleAxisf(static_cast<float>(rotationY_), vra));

    return kTranslation.matrix() * kRotationA.matrix() * kRotationB.matrix();
}

Eigen::Matrix4f Camera::SetProjection(double fov, double znear, double zfar) {
  fov_ = fov;
  zNear_ = znear;
  zFar_ = zfar;

  return SetProjection();
}

Eigen::Matrix4f Camera::SetProjection() const {
  const double kAR = static_cast<double>(viewportWidth_) /
                     static_cast<double>(viewportHeight_);
  glm::dmat4x4 glm_perspective =
      glm::perspective((fov_ * M_PI / 180.0), kAR, zNear_, zFar_);

  Eigen::Matrix4f eigen_perspective;
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      eigen_perspective(i, j) = static_cast<float>(glm_perspective[j][i]);

  return eigen_perspective;
}

void Camera::Zoom(double modifier) {
  distance_ += step_ * modifier;

  if (distance_ < kMinCameraDistance) distance_ = kMinCameraDistance;
  if (distance_ > kMaxCameraDistance) distance_ = kMaxCameraDistance;
}

void Camera::SafeZoom(double modifier) {
  if (zooming_) {
    Zoom(modifier - currentY_ < 0 ? -1 : 1);
    currentY_ = modifier;
  }
}

void Camera::SafePan(double x, double y) {
  if (panning_) {
    panX_ += (x - currentX_) / 10.0 * step_;
    panY_ -= (y - currentY_) / 10.0 * step_;
    currentY_ = y;
    currentX_ = x;
  }
}

void Camera::Rotate(double modifier) {
  rotationY_ += AngleIncrement * modifier;
}

void Camera::UpdateModel(Eigen::Vector3f min, Eigen::Vector3f max) {
  Eigen::Vector3d center = (min + max).cast<double>() / 2.0;
  centeringX_ = -center[0];
  centeringY_ = -center[1];
  centeringZ_ = -center[2];

  float longest_edge =
      std::max(max[0] - min[0], std::max(max[1] - min[1], max[2] - min[2]));
  scaling_ = 1.0 / static_cast<double>(longest_edge);
}

void Camera::SetRotationX(double y) {
  if (rotating_) {
    rotationX_ += (y - currentY_) * step_;
    currentY_ = y;
    if (rotationX_ < kMinRotationX) rotationX_ = kMinRotationX;
    if (rotationX_ > MaxRotationX) rotationX_ = MaxRotationX;
  }
}

void Camera::SetRotationY(double x) {
  if (rotating_) {
    rotationY_ += (x - currentX_) * step_;
    currentX_ = x;
  }
}

void Camera::StartRotating(double x, double y) {
  currentX_ = x;
  currentY_ = y;
  rotating_ = true;
}

void Camera::StopRotating(double x, double y) {
  currentX_ = x;
  currentY_ = y;
  rotating_ = false;
}

void Camera::StartZooming(double x, double y) {
  currentX_ = x;
  currentY_ = y;
  zooming_ = true;
}

void Camera::StopZooming(double x, double y) {
  currentX_ = x;
  currentY_ = y;
  zooming_ = false;
}

void Camera::StartPanning(double x, double y) {
  currentX_ = x;
  currentY_ = y;
  panning_ = true;
}

void Camera::StopPanning(double x, double y) {
  currentX_ = x;
  currentY_ = y;
  panning_ = false;
}

void Camera::SetCameraStep(double step) { this->step_ = step; }
