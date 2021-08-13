import threading
from concurrent.futures import ThreadPoolExecutor
import time


class Found:
    def __init__(self):
        self.is_found = False

    def done(self):
        self.is_found = True

    def isDone(self):
        return self.is_found


def badCharHeuristic(string, size):
    badChar = [-1] * 256
    for i in range(size):
        badChar[ord(string[i])] = i;
    return badChar


def search(txt, pat, found):
    # if found.isDone():
    #     return
    # m = len(pat)
    # n = len(txt)
    # badChar = badCharHeuristic(pat, m)
    # s = 0
    # while s <= n - m and found.isDone() is False:
    #     j = m - 1
    #     while j >= 0 and pat[j] == txt[s + j]:
    #         j -= 1
    #     if j < 0:
    #         found.done()
    #         return
    #     else:
    #         s += max(1, j - badChar[ord(txt[s + j])])
    if pat in txt:
        found.done()


# Driver program to test above function
def main():
    found = Found()
    with open("demofile2.txt") as infile:
        for idx, line in enumerate(infile):
            # search(line, "niddle", found)
            threads = []
            size = int(len(line)/2)  # group size
            overlap = len("niddle")  # overlap size
            for i in range(0, len(line), size - overlap):
                threads.append(threading.Thread(target=search, args=(line[i:i+size], "niddle", found)))
            for thread in threads:
                thread.start()
            for thread in threads:
                thread.join()
            if found.isDone():
                print("found in line {}".format(idx+1))
                return


if __name__ == '__main__':
    start = time.time()
    main()
    end = time.time()
    print(end - start)
    # f = open("demofile2.txt", "a")
    # for i in range(1, 200):
    #     for j in range(1,100000):
    #         f.write("line{} asdfjklfwjfidlsajfkewla;fjekla;f sjdkfudddeawfdjkfjweilsfijlsdkfjeiwlfkdjsielsfkjeislfjesifljiels!".format(i))
    # f.write("niddleadjfk")

