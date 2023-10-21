from dm_control import mjcf
import os

_HAND_XML = os.path.join(
    os.path.dirname(__file__),
    '../assets/hand/hand.xml',
)

class Hand():
    def __init__(self, name: str = None):
        self._mjcf_root = mjcf.from_path(_HAND_XML)
        if name:
            self._mjcf_root.model = name
        # Find MJCF elements that will be exposed as attributes.
        self._joints = self.mjcf_model.find_all('joint')
        self._bodies = self.mjcf_model.find_all('body')


    @property
    def joints(self):
        """List of joint elements belonging to the arm."""
        return self._joints

    @property
    def joints(self):
        """List of body elements belonging to the arm."""
        return self._bodies

    @property
    def mjcf_model(self):
        """Returns the `mjcf.RootElement` object corresponding to this robot."""
        return self._mjcf_root