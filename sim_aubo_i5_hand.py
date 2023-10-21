import time
import mujoco
import mujoco.viewer
from dm_control import mjcf
from pymjcf.hand import Hand
from pymjcf.arena import StandardArena
from pymjcf.aubo_i5 import AuboI5
from pymjcf.primitive import Primitive

# checkerboard floor
arena = StandardArena()

# robot hand
hand = Hand()

# aubo i5 arm
arm = AuboI5()

# adjust eef site
arm.eef_site.pos = [0.0, 0.0, -0.2]

# attach gripper to arm
arm.attach_tool(hand.mjcf_model, pos=[0, 0, -0.0075], quat=[0, 0, 0, 1])

# small box to be manipulated
box = Primitive(type="box", size=[0.035, 0.035, 0.035], pos=[0,0,0.035], rgba=[1, 0, 0, 1], friction=[1, 0.3, 0.0001])

# attach arm to arena
arena.attach(
    arm.mjcf_model, pos=[0,0,0]
)

# attach box to arena as free joint
arena.attach_free(
    box.mjcf_model, pos=[0.5,0,0]
)

# generate model
physics = mjcf.Physics.from_mjcf_model(arena.mjcf_model)

# put arm in a reasonable starting position
physics.bind(arm.joints).qpos = [0, 0, 1.5707, 0, 1.5707, 0]
physics.bind(arm.actuators).ctrl = [0, 0, 1.5707, 0, 1.5707, 0]

m = physics.model.ptr
d = physics.data.ptr
with mujoco.viewer.launch_passive(m, d) as viewer:
  # Close the viewer automatically after 30 wall-seconds.
  start = time.time()
  while viewer.is_running() and time.time() - start < 30:
    step_start = time.time()

    # step physics
    physics.step()

    # Pick up changes to the physics state, apply perturbations, update options from GUI.
    viewer.sync()

    # Rudimentary time keeping, will drift relative to wall clock.
    time_until_next_step = m.opt.timestep - (time.time() - step_start)
    if time_until_next_step > 0:
      time.sleep(time_until_next_step)