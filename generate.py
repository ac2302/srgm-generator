import subprocess
import json


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


def load_mapping(file="mappings/e-base.json"):
    with open(file, 'r')as f:
        return json.loads(f.read())


def load_srgm(mapping, file="test.srgm"):
    length = 0.5
    gap = 0.02

    specials = list(mapping['special'].values())

    with open(file, 'r')as f:
        srgm = f.read().split()

    final_srgm = []

    prev_note = None
    for i, s in enumerate(srgm):
        if s:   # gets rid of last empty line
            # filtrering comments
            if s[0] not in mapping['special']['comment']:
                # print(mapping['notes'][s])

                if s.startswith(mapping['special']['note-length']):
                    length = float(
                        s.replace(mapping['special']['note-length'], ''))
                    continue

                if s.startswith(mapping['special']['gap-length']):
                    gap = float(
                        s.replace(mapping['special']['gap-length'], ''))
                    continue

                if s == mapping['special']['hold']:
                    final_srgm[-1] = Sound(final_srgm[-1].duration + length,
                                           final_srgm[-1].frequency)
                    continue

                prev_note = s
                # if i+1 != len(srgm):
                #     if srgm[i+1] == s:

                play_length = length
                if i != 0:
                    if prev_note == s:
                        play_length -= gap
                        final_srgm.append(Sound(gap, 0))

                final_srgm.append(Sound(play_length, mapping['notes'][s]))

    return final_srgm


sounds = load_srgm(mapping=load_mapping(),
                   file="test-compositions/vs2.srgm")
# print(sounds)
save_sounds(sounds)

# sounds = [
#     Sound(0.5, 443),
#     Sound(0.5, 400),
#     Sound(0.5, 443),
#     Sound(0.5, 400),
#     Sound(0.5, 443),
#     Sound(0.5, 400)
# ]

# save_sounds(sounds)
