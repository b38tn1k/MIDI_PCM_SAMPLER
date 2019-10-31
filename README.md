# MIDI PCM Sampler

Trigger audio samples with the Beatstep for a crunchy lo-fi beat.

 It's noisy but also really quiet.
 
 [videos are easier than reading](https://youtu.be/oUzMPR78WlY)

This thing plays back lo-fi PCM samples generated using the [high-low tech](http://highlowtech.org/?p=1963) sketch when triggered by a MIDI note. I made some samples for Arduino playback in 2010 and only just remembered/found them.

I'm still waiting on that Behringer RD-8 to ship, this is a poor substitute.

I have it running on a Pro Trinket, you might need to change the number of samples depending on the memory of the Arduino variant you have.

1 Switch: halves sample time (sort of) and sounds even more lo-fi

3 Pots:

- 2 x 'Decay' Groups: set the length of the sample

- Glitchy Pitch Shift

GPIOs per the .ino sketch:
![Circuit Diagram](https://github.com/b38tn1k/MIDI_PCM_Sampler/blob/master/MIDI_PCM_SAMPLER.png)
