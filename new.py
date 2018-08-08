import time
import serial
import serial.tools.list_ports
# Will made this version... A little Different from before

if __name__ == '__main__':
    for port_no, description, address in serial.tools.list_ports.comports():
        if description == "Arduino":  # TODO: maybe platform dependent?
            port = port_no

    with serial.Serial(port=port_no, baudrate=9600, timeout=3) as ser:
        ser.read_until(b"<Arduino is ready>")  # We know we are initialized
        ser.write(b'hello')
        response = ser.readlines()

    print("The Arduino responded with:\n{}".format(
        "".join(x.decode("utf8") for x in response)))
