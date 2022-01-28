# Basic Phonebook
Basic implementation of a Phonebook in C language.

## Features
 - ### **Highly Tweakable**
    - **PhoneBook Format:** Can easily switch between CSV/TSV formats. Support for custom delimiters.
    - **Search Methods:** Can perform specific and lazy searches.
    - Memory Usage per Contact, UI Screens etc are easily modifiable as per end use.
- ### **Dynamic Memory Allocation**
    Application uses only as much memory as needed by selected PhoneBook. 

- ### **Partial Search Feature**
    Partial search queries are supported for easy navigation.

- ### **Interactive UI**
    Plain Text interactive UI focusing visibility and ease of use for a clutter free experience.

- ### **Machine/Human Readable PhoneBook Files**
    CSV/TSV Phonebook files are easily parseable whilst remaining accessible for manual edits


## How to test/run
1. Clone this repo using command below or download main branch archive `DS_Phonebook-main.zip`
    ```sh
    git clone https://github.com/rogue-geek/DS_Phonebook.git
    ```
2. Check for GCC using `gcc` command:
    ```sh
    gcc
    ```
    You should see some output like so. Else, install gcc for your platform.
    ```
    gcc: fatal error: no input files
    compilation terminated. 
    ```
3. Move into project folder. Execute appropriate run script.
    ```sh
    .\run.bat      # Powershell and Command Prompt (Windows)

    ./run.sh       # Linux Terminal
    ```

--------------------

## Problem Statement
<table>
<tr>
    <td><img src="qn.jpeg"></td>
    <td style="padding-left: 20px">
        Implement a phone book which stores name, phone number and email-id. Include the following features in your phone book.
        <li>Add new record</li>
        <li>Delete record</li>
        <li>Modify record</li>
        <li>Search record by phone number</li>
        <li>Search record by name</li>
        <li>Sort records by name</li>
    </td>
</tr>
</table>

----

## Development team
|#|Team Member|
|:-:|:----:|
|233|George P Zakaria|
|234|Gokul P. S.|
|235|Gokul Raj|
|236|Greeshma Biju R|