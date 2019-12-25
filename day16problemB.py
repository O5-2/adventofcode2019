from math import ceil

seed = "59718730609456731351293131043954182702121108074562978243742884161871544398977055503320958653307507508966449714414337735187580549358362555889812919496045724040642138706110661041990885362374435198119936583163910712480088609327792784217885605021161016819501165393890652993818130542242768441596060007838133531024988331598293657823801146846652173678159937295632636340994166521987674402071483406418370292035144241585262551324299766286455164775266890428904814988362921594953203336562273760946178800473700853809323954113201123479775212494228741821718730597221148998454224256326346654873824296052279974200167736410629219931381311353792034748731880630444730593"
digits = [int(i) for i in seed]*10000
offset = int(seed[:7])
digits = digits[offset:]

for i in range(0, 100):
    newDigits = []
    partialSum = sum(digits)
    for j in range(0, len(digits)):
        newDigits.append(abs(partialSum)%10)
        partialSum -= digits[j]
    digits = newDigits

print(digits[:8])

# That's an increase in time of a factor of one hundred million.
# There's got to be some clever trick.
# There must be some way to do it in phases*length time, instead of phases*length^2.
# 650,000,000 versus 4,225,000,000,000,000 operations.
# Yeah... 4.225 QUADRILLION (!) operations sounds pretty much impossible.
# Even at 100 million operations a second, it'd take 42.25 million seconds, so more than a year.
# Note: length^2 time (42,250,000,000,000 operations) would take 422.5 thousand seconds, so several days.
# It has to be phases*length.

# According to r/adventofcode:
# "The key observation for part 2 is that if your sequence has length n and you want to compute the value of the next phase at index i with i > n/2, then it's just the sum of all of the elements with index at least i. Therefore, we only need to compute the sequence for indices higher than the given offset at every phase, and we can do so in linear time."
# I'm kinda burnt out from 15B, so I'm not going to try tonight.

# Done.
