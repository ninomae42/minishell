import subprocess
import os

red = "\033[31m"
green = "\033[32m"
reset = "\033[0m"

def runtest(command):
    minishell_res = subprocess.run(["./minishell"], input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('=== input ===')
    print(f"[{command}]")
    print('=== stdout(minish) ===')
    print(f"{minishell_res.stdout}")
    print('=== stderr(minish) ===')
    print(f"{minishell_res.stderr}")
    bash_res = subprocess.run(["bash"], input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('=== input ===')
    print(f"[{command}]")
    print('=== stdout(bash) ===')
    print(f"{bash_res.stdout}")
    print('=== stderr(bash) ===')
    print(f"{bash_res.stderr}")

    if minishell_res.stdout != bash_res.stdout:
        print(f"=== {red}NG{reset} ===")
    else:
        print(f"=== {green}OK{reset} ===")

def runtest_with_path(command, path):
    print("=== path ===")
    print(f"[{path}]")
    if path != None:
        os.putenv("PATH", path)

    if path == None:
        minishell_res = subprocess.run(["./minishell"], env=None, input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    else:
        minishell_res = subprocess.run(["./minishell"], input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('=== input ===')
    print(f"[{command}]")
    print('=== stdout(minish) ===')
    print(f"{minishell_res.stdout}")
    print('=== stderr(minish) ===')
    print(f"{minishell_res.stderr}")
    if path == None:
        bash_res = subprocess.run(["bash"], env=None, input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    else:
        bash_res = subprocess.run(["bash"], input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('=== input ===')
    print(f"[{command}]")
    print('=== stdout(bash) ===')
    print(f"{bash_res.stdout}")
    print('=== stderr(bash) ===')
    print(f"{bash_res.stderr}")

    if minishell_res.stdout != bash_res.stdout:
        print(f"=== {red}NG{reset} ===")
    else:
        print(f"=== {green}OK{reset} ===")

if __name__ == '__main__':
    runtest('')
    runtest('/bin/ls')
    runtest('/bin/echo')
    runtest('/bin/echo hello')
    runtest('/bin/echo -n hello')
    runtest('ls')
    runtest('echo')
    runtest('echo hello')
    runtest('echo -n hello')
    runtest_with_path('ls', ':')
    runtest_with_path('ls', '')
    runtest_with_path('ls', None)

