import aiml
import time
time.clock = time.time

kernel = aiml.Kernel()
kernel.bootstrap(learnFiles="test.aiml")

while True:
    print("AIML: `{0}`".format(kernel.respond(input("Text: "))))