import subprocess

red = "\033[31m"
green = "\033[32m"
reset = "\033[0m"

def runtest(command):
    minishell_res = subprocess.run(["./minishell"], input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('=== input ===')
    print(f"[{command}]")
    print('=== stdout ===')
    print(f"{minishell_res.stdout}")
    print('=== stderr ===')
    print(f"{minishell_res.stderr}")
    bash_res = subprocess.run(["bash"], input=command, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print('=== input ===')
    print(f"[{command}]")
    print('=== stdout ===')
    print(f"{bash_res.stdout}")
    print('=== stderr ===')
    print(f"{bash_res.stderr}")

    if minishell_res.stdout != bash_res.stdout:
        print(f"=== {red}NG{reset} ===")
    else:
        print(f"=== {green}OK{reset} ===")


if __name__ == '__main__':
    runtest('')
    runtest('/bin/ls')
    runtest('/bin/echo')

