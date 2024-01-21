import os
from manipulator.robot.gripper import Gripper

_HAND_XML = os.path.join(
    os.path.dirname(__file__),
    '../assets/robot/hand/hand.xml',
)

_JOINTS = [
    'Wrist_1',
    'Wrist_2',
    'Thumb_CMC',
    'Thumb_MCP',
    'Thumb_IP',
    'Index_CMC',
    'Index_MCP',
    'Index_IP',
    'Middle_CMC',
    'Middle_MCP',
    'Middle_IP',
    'Ring_CMC',
    'Ring_MCP',
    'Ring_IP',
    'Pinky_CMC',
    'Pinky_MCP',
    'Pinky_IP'
    ]

_ACTUATORS = [
    'wrist_1_joint',
    'wrist_2_joint',
    'Thumb_CMC',
    'Thumb_MCP',
    'Thumb_IP',
    'Index_CMC',
    'Index_MCP',
    'Index_IP',
    'Middle_CMC',
    'Middle_MCP',
    'Middle_IP',
    'Ring_CMC',
    'Ring_MCP',
    'Ring_IP',
    'Pinky_CMC',
    'Pinky_MCP',
    'Pinky_IP',
]

class Hand(Gripper):
    def __init__(self, name: str = None):
        super().__init__(_HAND_XML, _JOINTS, _ACTUATORS, name)