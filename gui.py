import sys
import subprocess
#import  PyQt5
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QPushButton, QWidget

class ResourceMonitorApp(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Resource Monitor")
        self.setGeometry(100, 100, 400, 200)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.layout = QVBoxLayout()
        self.central_widget.setLayout(self.layout)

        self.cpu_label = QLabel("CPU Usage: N/A")
        self.memory_label = QLabel("Memory Usage: N/A")
        self.disk_label = QLabel("Disk Usage: N/A")

        self.layout.addWidget(self.cpu_label)
        self.layout.addWidget(self.memory_label)
        self.layout.addWidget(self.disk_label)

        self.update_button = QPushButton("Update")
        self.layout.addWidget(self.update_button)

        self.update_button.clicked.connect(self.update_resource_info)

    def update_resource_info(self):
        try:
            # Run your C++ program using subprocess and capture its output
            result = subprocess.check_output(["./build/resource_monitor"])
            output_lines = result.decode("utf-8").splitlines()

            # Update labels with resource information
            self.cpu_label.setText(output_lines[0])
            self.memory_label.setText(output_lines[1])
            self.disk_label.setText(output_lines[2])
        except subprocess.CalledProcessError as e:
            # Handle any errors that occur when running the C++ program
            self.cpu_label.setText("Error: Failed to get CPU usage")
            self.memory_label.setText("Error: Failed to get memory usage")
            self.disk_label.setText("Error: Failed to get disk usage")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = ResourceMonitorApp()
    window.show()
    sys.exit(app.exec_())
