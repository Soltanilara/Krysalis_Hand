import time
import mujoco
import mujoco.viewer
from dm_control import mjcf
from pymjcf.hand import Hand
from pymjcf.arena import StandardArena

# checkerboard floor
arena = StandardArena()

hand = Hand()

# attach hand to arena
arena.attach(
    hand.mjcf_model, pos=[0,0,0]
)

# generate model
physics = mjcf.Physics.from_mjcf_model(arena.mjcf_model)

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