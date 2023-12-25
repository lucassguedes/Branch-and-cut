import subprocess



def main():

    result = subprocess.run(["ls", "../instances/"], capture_output=True, text=True)
    instance_names = result.stdout.split("\n")
    instance_names.pop()

    output = ""
    counter = 0;
    n_instances = len(instance_names)
    for instance_name in instance_names:
        print(f"Executing \"{instance_name}\" instance...")
        print(f"Total progress: {counter}/{n_instances}") 
        result = subprocess.run(["../bc", f"../instances/{instance_name}"], capture_output=True, text=True)

        separated_result = result.stdout.split("\n")
        objValue = separated_result[0]
        time = separated_result[1]
        output+=instance_name + "\n\tobj: " + objValue + "\n\ttime: " + time + "\n" 
        print("\033[H")
        counter+=1

    with open("test_result.txt", "w") as file:
        file.write(output)
        








if __name__ == "__main__":
    main()
