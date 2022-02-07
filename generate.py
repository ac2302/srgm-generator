import subprocess


class Sound:
    def __init__(self, duration, frequency):
        self.duration = duration
        if frequency > 0:
            self.frequency = frequency
            self.amplitude = 1
        else:
            self.frequency = 443
            self.amplitude = 0


def save_sounds(sounds, file="output/test.au"):
    final_output = b''

    output, err = subprocess.Popen(
        ['./gen-header'], stdout=subprocess.PIPE).communicate()
    final_output += output

    for s in sounds:
        output, err = subprocess.Popen(
            ['./gen-freq', str(s.duration), str(s.frequency),
             str(s.amplitude)],
            stdout=subprocess.PIPE).communicate()
        final_output += output

    with open(file, 'xb') as f:
        f.write(final_output)


sounds = [
    Sound(0.5, 443),
    Sound(0.5, 400),
    Sound(0.5, 443),
    Sound(0.5, 400),
    Sound(0.5, 443),
    Sound(0.5, 400)
]

save_sounds(sounds)
