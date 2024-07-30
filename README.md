# Drone_robotics_rescue_mission
The objective of this project is to use a drone equipped with a camera to detect a person using YOLOv2 (You Only Look Once version 2), a popular object detection algorithm. If a person is detected, the drone will land to facilitate a rescue. If no person is detected, the drone will follow a predetermined square route and progressively cover smaller squares inside the initial square area.

Detection with Camera:
        The drone has a camera that uses a special program called YOLOv2 to detect objects. This program can identify various things in the camera’s view, including people.

Action When a Person is Detected:
        When the drone’s camera detects a person, it will record the time of detection and immediately prepare to land. This action is taken to assist in the rescue operation.

search Pattern When No Person is Detected:
        If no person is detected, the drone will start a predefined search pattern.
        The search pattern is a series of squares. The drone flies in a large square first.
        After completing the large square, the drone will reduce the size of the square and repeat the search.
        This process continues with smaller and smaller squares until the drone has covered the entire area thoroughly.

Final Action:
        The drone follows the search pattern to cover a large area efficiently.
        If a person is found during the search, the drone lands to perform the rescue.
        If the search pattern is completed without detecting a person, the drone will land after finishing the entire search.

This method ensures that the drone can both perform a thorough search over a large area and respond quickly if a person is detected.

steps:
        
        roslaunch iq_sim runway.launch
(This command launches the runway.launch file from the iq_sim package.)
    
    ~/startsitl.sh
(The startsitl.sh script is likely used to start the SITL (Software In The Loop) simulation for a flight control system, such as ArduPilot or PX4. SITL allows for testing and simulation of the flight control software without the need for actual hardware.)
[sitl](https://github.com/user-attachments/assets/235a28e0-0166-4fc5-871e-bbdb48c04acb)![sitl](https://github.com/user-attachments/assets/195bcd7b-8600-4699-a95e-32fcf8503b46)
    
    roslaunch iq_sim apm.launch!

(This launch file is typically used to start the simulation components related to the APM (ArduPilot Mega) or PX4 autopilot system within the simulation environment. It could include the configuration of the autopilot system, starting necessary nodes, and integrating it with the simulation.)
    
![apm](https://github.com/user-attachments/assets/814cda12-174c-4dc3-a3de-f10dc1fb435e)

    roslaunch darknet_ros darknet_ros.launch
(This launch file starts the YOLO object detection system using Darknet within ROS. It initializes the nodes that handle object detection using the YOLOv2 or YOLOv3 algorithm. This is essential for detecting objects in camera feeds, such as people, as part of the robot’s perception system.)

![sr](https://github.com/user-attachments/assets/7ae1cd9c-2c64-4a20-a0b3-48bff9eee3f1)
![sr2](https://github.com/user-attachments/assets/cff67a29-7a65-452e-8bd8-0ecd142ea37d)

https://github.com/user-attachments/assets/916b2a85-229c-41f4-9458-182b0242f387


    
