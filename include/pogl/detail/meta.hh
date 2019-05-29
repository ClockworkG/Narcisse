#pragma once

#include <pogl/camera.hh>
#include <pogl/scene.hh>

#include <GL/glew.h>

#include <boost/hana.hpp>

namespace hana = boost::hana;

BOOST_HANA_ADAPT_STRUCT(
    pogl::SceneSettings,
    camera,
    background
);

BOOST_HANA_ADAPT_STRUCT(
    pogl::CameraSettings,
    position,
    target,
    up,
    fov,
    aspect_ratio,
    z_near,
    z_far
);
