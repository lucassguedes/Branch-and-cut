import subprocess



def main():
    instances_folder = "../instances/under_300/"
    output_filename = "under_300.txt"

    result = subprocess.run(["ls", instances_folder], capture_output=True, text=True)
    instance_names = result.stdout.split("\n")
    instance_names.pop()

    output = ""
    counter = 1
    n_instances = len(instance_names)
    for instance_name in instance_names:
        print("\033[H")
        print(f"Executing \"{instance_name}\" instance...")
        print(f"Total progress: {counter}/{n_instances}") 
        result = subprocess.run(["../bc", f"{instances_folder}{instance_name}"], capture_output=True, text=True)

        separated_result = result.stdout.split("\n")
        objValue = separated_result[0]
        time = separated_result[1]
        output+=instance_name + "\n\tobj: " + objValue + "\n\ttime: " + time + "\n" 
        counter+=1

    with open(output_filename, "w") as file:
        file.write(output)
        








if __name__ == "__main__":
    main()
