import subprocess



def main():

    result = subprocess.run(["ls", "../instances/"], capture_output=True, text=True)
    instance_names = result.stdout.split("\n")
    instance_names.pop()

    print("Instâncias:")
    print(instance_names)


    output = ""
    for instance_name in instance_names:
        result = subprocess.run(["../bc", f"../instances/{instance_name}"], capture_output=True, text=True)
        output+=instance_name + ": " + result.stdout + "\n"

    with open("test_result.txt", "w") as file:
        file.write(output)
        








if __name__ == "__main__":
    main()
