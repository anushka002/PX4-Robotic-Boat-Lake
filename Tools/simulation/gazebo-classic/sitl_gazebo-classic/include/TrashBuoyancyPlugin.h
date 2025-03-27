#ifndef TRASH_BUOYANCY_PLUGIN_H
#define TRASH_BUOYANCY_PLUGIN_H

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/Model.hh>
#include <gazebo/physics/World.hh>
#include <gazebo/physics/Link.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Pose3.hh>

namespace gazebo
{
class TrashBuoyancyPlugin : public ModelPlugin
{
public:
    // Constructor
    TrashBuoyancyPlugin();
    
    // Destructor
    virtual ~TrashBuoyancyPlugin();

    // Required Gazebo plugin method to load the plugin
    void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) override;

protected:
    // Update callback method
    void OnUpdate();

private:
    // Gazebo communication and update connection
    event::ConnectionPtr updateConnection;

    // Pointer to the model
    physics::ModelPtr model;

    // Pointer to the world
    physics::WorldPtr world;

    // Link to apply buoyancy forces
    physics::LinkPtr mainLink;

    // Plugin configuration parameters
    double waterDensity;
    double waterLevel;
    double buoyancyFactor;
    double dragCoefficient;

    // Positioning parameters
    ignition::math::Vector3d initialPosition;
    ignition::math::Quaterniond initialRotation;

    // Simulation parameters
    bool debugMode;

    // Internal methods
    void ApplyBuoyancyForces();
    void ApplyDragForces();
    void ValidateAndCorrectPosition();
    void LogDebugInformation();
};

// Register the plugin with Gazebo
GZ_REGISTER_MODEL_PLUGIN(TrashBuoyancyPlugin)
}

#endif // TRASH_BUOYANCY_PLUGIN_H
