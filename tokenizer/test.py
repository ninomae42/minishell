import subprocess

red = "\033[31m"
green = "\033[32m"
reset = "\033[0m"

basicTest = [
   'hogehoge',
   '/bin/ls',
   'cat hoge.txt',
   'cat  hoge.txt',
   'cat\thoge.txt',
]

quoteCharacterTest = [
    "echo 'hogehoge'",
    'echo "hogehoge"',
    "echo 'hoge hoge'",
    'echo "hoge hoge"',
    # 'echo "hogehoge" >> out.txt',
]


pipeRedirectionTest = [
   'cat hoge.txt | grep ft',
   'cat hoge.txt | grep ft > out.txt',
   'cat hoge.txt | grep ft >> out.txt',
   '<cat hoge.txt | grep ft out.txt',
   '<cat hoge.txt | grep ft > out.txt',
   '<cat hoge.txt | grep ft >> out.txt',
]

invalidInputTest = [
   r'echo "hoge hoge"',
   r"echo 'hoge'hoge'",
   'echo "hoge\'hoge"',
   r'echo "hoge\"hoge"',
]

operatorTest = [
    "cat test.txt > result.out",
    "cat test.txt | grep ft > result.out",
    "cat test.txt | grep ft >> result.out",
    "<test.txt cat | grep ft >> result.out",
    "<<EOF cat | grep ft >> result.out",
]

def test_tokenizer(inputStr):
    for i, input in enumerate(inputStr):
        command = ["./tokenizer", input]
        runtest(i, command)

def runtest(index, command):
    res = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    print(f'===== TEST{index} =====')
    print('=== input ===')
    print(f"[{res.args[1]}]")
    print('=== stdout ===')
    print(f"{res.stdout.decode()}")
    print('=== stderr ===')
    print(f"{res.stderr.decode()}")

    if res.returncode == 0:
        print(f'===== TEST{index} {green} OK {reset} =====\n')
    else:
        print(f'===== TEST{index} {red} NG {reset} =====\n')

if __name__ ==  '__main__':
    test_tokenizer(basicTest)
    test_tokenizer(quoteCharacterTest)
    # test_tokenizer(pipeRedirectionTest)
    # test_tokenizer(invalidInputTest)
    # test_tokenizer(operatorTest)
