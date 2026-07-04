from direct.showbase.ShowBase import ShowBase
from panda3d.core import DirectionalLight, AmbientLight, Vec4
import subprocess
import os

class AIAgentSimulation(ShowBase):
    def __init__(self):
        # Initialize the native Panda3D Engine context window
        ShowBase.__init__(self)
        
        print("=======================================================")
        
        # 1. Setup Environment Bounds and Camera Matrix
        self.setBackgroundColor(0.1, 0.1, 0.15, 1.0) # Slate dark workspace
        self.cam.setPos(0, -30, 10)
        self.cam.lookAt(0, 0, 0)
        
        # 2. Build a Visual Grid World Placeholder using Panda3D primitives
        # We simulate an 8-slot array stream line visually in 3D coordinate spaces
        self.agent_x = 0
        self.target_threshold = 22
        
        # 3. Load basic visual markers
        self.spawn_environment_lighting()
        self.load_simulation_objects()

        # 4. Bind keyboard input hooks to trigger the low-latency C++ validation core
        self.accept("arrow_left", self.move_agent, [-1])
        self.accept("arrow_right", self.move_agent, [1])
        self.accept("space", self.evaluate_bounds_via_cpp_core)
        
        print(" [INFO] 3D Panda3D Ingestion Grid Live.")
        print(" Press Left/Right Arrows to shift Agent index. Press SPACE to execute C++ core math.")
        print("=======================================================")

    def spawn_environment_lighting(self):
        # Add basic scene lights for clear visual dimension tracing
        ambient_light = AmbientLight("ambient_light")
        ambient_light.setColor(Vec4(0.3, 0.3, 0.3, 1.0))
        al_node = self.render.attachNewNode(ambient_light)
        self.render.setLight(al_node)

    def load_simulation_objects(self):
        # Dynamically load the default panda model as our AI agent token actor
        self.agent_node = self.loader.loadModel("models/panda")
        self.agent_node.setScale(0.5)
        self.agent_node.setPos(self.agent_x, 0, 0)
        self.agent_node.reparentTo(self.render)

    def move_agent(self, direction):
        # Clamp bounds between 0 and 7 to prevent memory faults inside our data stream
        new_x = self.agent_x + direction
        if 0 <= new_x <= 7:
            self.agent_x = new_x
            self.agent_node.setX(self.agent_x * 2) # Offset scaling factor for 3D visibility
            print(f" Agent shifted to Array Slot Index Boundary: [{self.agent_x}]")

    def evaluate_bounds_via_cpp_core(self):
        print(f"\n[SYSTEM] Invoking C++ Binary to check slice [{0} to {self.agent_x}]...")
        
        # Determine the relative binary name based on local OS layer
        executable = "./range_engine"
        if os.name == 'nt': # Windows System Check
            executable = "range_engine.exe"
            
        # Execute your compiled static range engine as a sub-process
        # Passes the current index bounding vectors dynamically via argv parameters!
        try:
            result = subprocess.run(
                [executable, "0", str(self.agent_x), str(self.target_threshold)],
                capture_output=True, text=True, check=True
            )
            print(result.stdout)
        except subprocess.CalledProcessError as e:
            print(f"[ERROR] Failed execution map inside binary layer: {e.stderr}")
        except FileNotFoundError:
            print("[ERROR] range_engine binary not found in root path. Compile main.cpp first!")

if __name__ == "__main__":
    sim = AIAgentSimulation()
    sim.run()