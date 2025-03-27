#include "TrashBuoyancyPlugin.h"
#include <gazebo/common/Assert.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo
{

TrashBuoyancyPlugin::TrashBuoyancyPlugin() :
    waterDensity(997.7735),     // Default water density
    waterLevel(1),         // Default water surface level
    buoyancyFactor(9.81),    // Gravitational acceleration factor
    dragCoefficient(0.47),   // Default drag coefficient
    debugMode(false)         // Debug logging off by default
{
}

TrashBuoyancyPlugin::~TrashBuoyancyPlugin()
{
}

void TrashBuoyancyPlugin::Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
{
    // Sanity check
    GZ_ASSERT(_model, "TrashBuoyancyPlugin requires a valid model");

    this->model = _model;
    this->world = _model->GetWorld();
    this->mainLink = _model->GetLink();

    // Read configuration from SDF
    if (_sdf->HasElement("water_density"))
        waterDensity = _sdf->Get<double>("water_density");
    
    if (_sdf->HasElement("water_level"))
        waterLevel = _sdf->Get<double>("water_level");
    
    if (_sdf->HasElement("buoyancy_factor"))
        buoyancyFactor = _sdf->Get<double>("buoyancy_factor");
    
    if (_sdf->HasElement("drag_coefficient"))
        dragCoefficient = _sdf->Get<double>("drag_coefficient");
    
    if (_sdf->HasElement("debug_mode"))
        debugMode = _sdf->Get<bool>("debug_mode");

    // Store initial position and rotation
    #if GAZEBO_MAJOR_VERSION >= 8
        initialPosition = this->mainLink->WorldPose().Pos();
        initialRotation = this->mainLink->WorldPose().Rot();
    #else
        initialPosition = this->mainLink->GetWorldPose().Ign().Pos();
        initialRotation = this->mainLink->GetWorldPose().Ign().Rot();
    #endif

    // Connect to the world update event
    this->updateConnection = event::Events::ConnectWorldUpdateBegin(
        std::bind(&TrashBuoyancyPlugin::OnUpdate, this));

    gzmsg << "TrashBuoyancyPlugin initialized for model: " 
          << _model->GetName() << std::endl;
}

void TrashBuoyancyPlugin::OnUpdate()
{
    ValidateAndCorrectPosition();
    ApplyBuoyancyForces();
    ApplyDragForces();

    if (debugMode)
        LogDebugInformation();
}

void TrashBuoyancyPlugin::ValidateAndCorrectPosition()
{
    #if GAZEBO_MAJOR_VERSION >= 8
        auto currentPose = this->mainLink->WorldPose();
    #else
        auto currentPose = this->mainLink->GetWorldPose().Ign();
    #endif

    // Implement bounds checking and correction
    if (std::abs(currentPose.Pos().X() - initialPosition.X()) > 100.0 ||
        std::abs(currentPose.Pos().Y() - initialPosition.Y()) > 100.0)
    {
        // Reset to initial position if drifted too far
        this->mainLink->SetWorldPose(
            ignition::math::Pose3d(initialPosition, initialRotation)
        );
    }
}

void TrashBuoyancyPlugin::ApplyBuoyancyForces()
{
    // Simplified buoyancy calculation
    #if GAZEBO_MAJOR_VERSION >= 8
        auto currentPose = this->mainLink->WorldPose();
        auto velocity = this->mainLink->WorldLinearVel();
    #else
        auto currentPose = this->mainLink->GetWorldPose().Ign();
        auto velocity = this->mainLink->GetWorldLinearVel().Ign();
    #endif

    // Check if object is below water level
    if (currentPose.Pos().Z() < waterLevel)
    {
        // Calculate submerged volume (simplified)
        double submergenceDepth = waterLevel - currentPose.Pos().Z();
        double objectVolume = this->mainLink->GetInertial()->Mass() / waterDensity;

        // Buoyancy force calculation
        double buoyancyForce = waterDensity * buoyancyFactor * objectVolume * submergenceDepth;

        // Apply upward buoyancy force
        this->mainLink->AddForce(
            ignition::math::Vector3d(0, 0, buoyancyForce)
        );
    }
}

void TrashBuoyancyPlugin::ApplyDragForces()
{
    #if GAZEBO_MAJOR_VERSION >= 8
        auto velocity = this->mainLink->WorldLinearVel();
    #else
        auto velocity = this->mainLink->GetWorldLinearVel().Ign();
    #endif

    // Simplified hydrodynamic drag
    double velocityMagnitude = velocity.Length();
    if (velocityMagnitude > 0)
    {
        // Drag force calculation
        double dragForce = 0.5 * waterDensity * dragCoefficient * 
                           this->mainLink->GetInertial()->Mass() * 
                           velocityMagnitude * velocityMagnitude;

        // Apply drag in opposite direction of motion
        ignition::math::Vector3d dragDirection = -velocity.Normalized();
        this->mainLink->AddForce(dragDirection * dragForce);
    }
}

void TrashBuoyancyPlugin::LogDebugInformation()
{
    #if GAZEBO_MAJOR_VERSION >= 8
        auto currentPose = this->mainLink->WorldPose();
        auto velocity = this->mainLink->WorldLinearVel();
    #else
        auto currentPose = this->mainLink->GetWorldPose().Ign();
        auto velocity = this->mainLink->GetWorldLinearVel().Ign();
    #endif

    gzdbg << "Trash Object Debug Info:" << std::endl;
    gzdbg << "Position: " << currentPose.Pos() << std::endl;
    gzdbg << "Velocity: " << velocity << std::endl;
    gzdbg << "Water Level: " << waterLevel << std::endl;
}

} // namespace gazebo
