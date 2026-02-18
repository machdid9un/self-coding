#include "Utils.hpp"

#include <algorithm>

static const long long kPs[] = {
    45238972, 78312467, 15927486, 67219356, 81437961, 50612793, 79341829,
    23791841, 69517283, 42831769, 73916285, 98371249, 35497183, 61527389,
    18294763, 56419837, 72149387, 84173925, 69428371, 15879243, 87216439,
    36729185, 59182743, 72948163, 13674928, 64928371, 85713926, 49381725,
    78624931, 25839147, 61289734, 74126389, 36581947, 51927364, 79361824,
    15492736, 68943127, 82173654, 42985713, 57381926, 39172485, 72649381,
    83571924, 19483726, 65829174, 71368259, 52491873, 38719625, 64928375,
    81293746, 59371826, 27163849, 48729136, 63917284, 78519362, 12983764,
    47193825, 65287149, 38745192, 93628174, 58371926, 72163849, 48931725,
    67129384, 75291863, 19384725, 69812734, 51729386, 43981725, 67291834,
    81273945, 39481726, 75629138, 12893764, 61372984, 72918364, 15827394,
    59713824, 38471926, 72193846, 46291738, 59387124, 81927364, 74561938,
    67123849, 52731849, 38917265, 69381725, 47291836, 85371926, 61928374,
    75461928, 19283746, 53829174, 61293748, 72948136, 38472619, 57192834,
    69827314, 24791836, 57
};
static const long long kDs = 84927481;

struct RandomState {
    long long studentID;
    long long cs;
    long long ls;
    long long gi;
};

static RandomState gRandomState = {0, 0, 0, 0};

void initRandom(const std::string& sid) {
    gRandomState.studentID = 0;
    for (size_t i = 0; i < sid.size(); ++i) {
        if (sid[i] < '0' || sid[i] > '9') continue;
        gRandomState.studentID = gRandomState.studentID * 10 + (sid[i] - '0');
    }
    gRandomState.cs = gRandomState.studentID % kDs;
    if (sid.size() >= 7) {
        gRandomState.ls = 0;
        for (size_t i = 4; i < 7 && i < sid.size(); ++i) {
            gRandomState.ls = gRandomState.ls * 10 + (sid[i] - '0');
        }
    } else {
        gRandomState.ls = gRandomState.studentID % 1000;
    }
    gRandomState.gi = 0;
}

long long nextRandom() {
    gRandomState.cs = (gRandomState.cs + kPs[gRandomState.gi]) %
                      (kDs + gRandomState.ls +
                       kPs[(gRandomState.gi + 1) % (sizeof(kPs) / sizeof(kPs[0]))] % kDs);
    gRandomState.gi = (gRandomState.gi + 1) % (sizeof(kPs) / sizeof(kPs[0]));

    long long temp = gRandomState.cs;

    gRandomState.cs = (gRandomState.cs + kPs[gRandomState.gi]) %
                      (kDs + gRandomState.ls +
                       kPs[(gRandomState.gi + 1) % (sizeof(kPs) / sizeof(kPs[0]))] % kDs);

    gRandomState.gi = (gRandomState.gi + 1) % (sizeof(kPs) / sizeof(kPs[0]));

    gRandomState.cs *= temp;

    return gRandomState.cs;
}

int randomRange(int maxExclusive) {
    if (maxExclusive <= 0) return 0;
    long long r = nextRandom();
    if (r < 0) r = -r;
    return static_cast<int>(r % maxExclusive);
}

int wrapWithFieldSize(int value) {
    int r = value % FIELD_SIZE;
    if (r < 0) r += FIELD_SIZE;
    return r;
}

Location wrapLocation(int x, int y) {
    Location loc;
    loc.x = wrapWithFieldSize(x);
    loc.y = wrapWithFieldSize(y);
    return loc;
}

Location randomSelection(const std::vector<Location>& candidates) {

    if (candidates.empty()) {
        throw std::invalid_argument("candidates is empty");
    }

    std::vector<Location> sorted = candidates;
    std::sort(sorted.begin(), sorted.end(),
              [](const Location& a, const Location& b) {
                  if (a.x != b.x) return a.x < b.x;
                  return a.y < b.y;
              });

    int idx = randomRange(static_cast<int>(sorted.size()));
    return sorted[idx];
}

void shuffleLocations(std::vector<Location>& locations) {
    for (int i = static_cast<int>(locations.size()) - 1; i > 0; --i) {
        int j = randomRange(i + 1);
        if (j == i) continue;
        Location temp = locations[i];
        locations[i] = locations[j];
        locations[j] = temp;
    }
}
