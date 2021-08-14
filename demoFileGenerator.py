if __name__ == '__main__':
    f = open("fileName.txt", "a")
    for i in range(1, 200):
        for j in range(1,100000):
            if i == 193 and j == 100:
                f.write("line{} niddlelfwjfidlsajfkewla;fjekla;f sjdkfudddeawfdjkfjweilsfijlsdkfjeiwlfkdjsielsfkjeislfjesifljiels!".format(i))
            else:
                f.write("line{} asdfjklfwjfidlsajfkewla;fjekla;f sjdkfudddeawfdjkfjweilsfijlsdkfjeiwlfkdjsielsfkjeislfjesifljiels!".format(i))
        f.write("\n")

