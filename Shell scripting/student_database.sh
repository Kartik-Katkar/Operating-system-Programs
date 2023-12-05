#!/bin/bash

DATABASE_FILE="students_database.txt"

# Function to display the menu
display_menu() {
    echo "1. Insert student"
    echo "2. Update student"
    echo "3. Delete student"
    echo "4. Display database"
    echo "5. Exit"
}

# Function to insert a student
insert_student() {
    echo "Enter student details:"
    read -p "Name: " name
    read -p "Roll number: " roll_number
    read -p "Grade: " grade

    echo "$name|$roll_number|$grade" >> "$DATABASE_FILE"
    echo "Student inserted successfully!"
}

# Function to update a student
update_student() {
    read -p "Enter the roll number of the student to update: " roll_number
    if grep -q "$roll_number" "$DATABASE_FILE"; then
        echo "Enter updated details:"
        read -p "Name: " name
        read -p "Grade: " grade

        # Update the data in the file
        sed -i "/$roll_number/c\\$name|$roll_number|$grade" "$DATABASE_FILE"
        echo "Student updated successfully!"
    else
        echo "Student with roll number $roll_number not found."
    fi
}

# Function to delete a student
delete_student() {
    read -p "Enter the roll number of the student to delete: " roll_number
    if grep -q "$roll_number" "$DATABASE_FILE"; then
        # Delete the line containing the student's data
        sed -i "/$roll_number/d" "$DATABASE_FILE"
        echo "Student deleted successfully!"
    else
        echo "Student with roll number $roll_number not found."
    fi
}

# Function to display the database
display_database() {
    echo "Student Database:"
    echo "-----------------"
    cat "$DATABASE_FILE"
    echo "-----------------"
}

# Main loop
while true; do
    display_menu

    read -p "Enter your choice: " choice

    case $choice in
        1) insert_student;;
        2) update_student;;
        3) delete_student;;
        4) display_database;;
        5) echo "Exiting program. Goodbye!"; exit;;
        *) echo "Invalid choice. Please enter a number between 1 and 5.";;
    esac
done
