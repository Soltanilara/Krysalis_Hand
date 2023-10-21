from dm_control import mjcf
import numpy as np
import os

_AUBOI5_XML = os.path.join(
    os.path.dirname(__file__),
    '../assets/aubo_i5/aubo_i5.xml',
)

_JOINTS = (
    'shoulder_pan_joint',
    'shoulder_lift_joint',
    'elbow_joint',
    'wrist_1_joint',
    'wrist_2_joint',
    'wrist_3_joint',
)

_EEF_SITE = 'eef_site'

_ATTACHMENT_SITE = 'attachment_site'

class AuboI5():
    def __init__(self, name: str = None):
        self._mjcf_root = mjcf.from_path(_AUBOI5_XML)
        if name:
            self._mjcf_root.model = name

        # Find MJCF elements that will be exposed as attributes.
        self._joints = [self._mjcf_root.find('joint', name) for name in _JOINTS]
        self._eef_site = self._mjcf_root.find('site', _EEF_SITE)
        self._attachment_site = self._mjcf_root.find('site', _ATTACHMENT_SITE)
        self._actuators = self._mjcf_root.actuator.all_children()

    @property
    def joints(self):
        """List of joint elements belonging to the arm."""
        return self._joints

    @property
    def eef_site(self):
        """Wrist site of the arm (attachment point for the hand)."""
        return self._eef_site
    
    @property
    def actuators(self):
        """List of actuator elements belonging to the arm."""
        return self._actuators

    @property
    def mjcf_model(self):
        """Returns the `mjcf.RootElement` object corresponding to this robot."""
        return self._mjcf_root
    
    def attach_tool(self, child, pos: list = [0, 0, 0], quat: list = [1, 0, 0, 0]) -> mjcf.Element:
        frame = self._attachment_site.attach(child)
        frame.pos = pos
        frame.quat = quat
        return frame