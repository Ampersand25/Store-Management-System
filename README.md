# Store-Management-System
<strong>Description</strong>:
- Qt Widgets Application for Windows (desktop app) that manages the items (products) of a virtual store
- the app has a layered architecture: presentation layer (UI and GUI), business layer (service), infrastructure layer (repositories), validation layer (validators for the entities) and domain layer (entities from the domain of the problem)
- data (products/items from the store) can be stored/saved in memory, in a text file or in a MySQL database
- saving data in a database works for both debug and release configurations
- shopping cart is not persistent (is only saved in memory)
- the app was developed in Visual Sudio 2022 Community IDE using C++ and QT Framework (version 6.5.0)
- the app contains the following Qt modules: Qt Core, Qt GUI and Qt Widgets
- configuration was set to debug when creating the app
- platform is x64

<strong>The design patterns used in developing the application are</strong>:
- Observer (also known as publish-subscribe). For example the windows that displays the content of the shopping cart are all observers/subscribers and the shopping cart is the observable/publisher, which means that the a new item is added or removed from the shopping cart, all the windows that are related to the shopping cart will display the new content of the shopping cart that the user has created (each modification/update of the shopping cart will result in the windows being notified about the changes)
- Model View (Qt version of MVC (Model View Controller)). The application uses models for all the lists and tables (each list is a QListView and each table is a QTableView and both have a model)

<strong>The application has the following features</strong>:
- CRUD operations on the products/items from the store: an user can add a new product/item, can update the type and/or price of an existing product/item, can delete an existing product/item and can search for a specific product/item
- undo operation: the user can undo the last operation that was executed (for example if the last operation was delete/remove, if the user chooses to undo it, then the deleted/removed product/item will be added back in the store)
- sorting products: the user can sort the existing products after name, type, name + type (if two products have the same name then they will be sorted according to their type), price and producer. The sorting can be both ascending and descending
- filtering the existing items from the virtual store: the user can filter all the items that have a specific name, specific type, specific price, or specific producer. When filtering by price, there is the possibility to filter all the items that have a price less than a value, equal to a value, or greater than a value. The list will display items that match the applied filter in green, while items that don't match will be displayed in red. The table will only show the items that have been filtered
- selecting an item from the list: if the user selects an item from the list then a message box, containing the details about the selected product (name, type, price and producer), will be displayed
- adding a new product to the shopping cart: the user can add an existing product from the store to the shopping cart
- generating items/products for the shopping cart: the user can randomly generate a number (between 1 and 100) of products for its shopping cart
- emptying the shopping cart: the user can empty the shopping cart by removing all the products from it
- exporting the shopping cart: the user can export the content of the shopping cart to a CSV (Comma-Separated Values) or/and an HTML (HyperText Markup Language) file. The name of the file(s) must be given by the user. The exporting file(s) will be created inside the project directory in the folder named "Export cos cumparaturi". For opening CSV files, it is recommended to use Excel, and for opening HTML files, it is recommended to use a web browser such as Google Chrome. However, both types of files can also be opened using a text editor such as Notepad or Notepad++
- selecting an item from the shopping cart list: if the user selects an item from the shopping cart then a message box, containing the details about the selected product (name, type, price and producer), will be displayed

<strong>While developing the app I also worked with tools such as</strong>:
- memory leak detector (for detecting memory leaks)
- debugger (for fixing bugs)
- CPU profiler from Diagnostic Tools (which measures the performance of the application (the app is recommended to be set to Release mode and not Debug, so that it can benefit from all possible optimizations))
- OpenCppCoverage (for seeing how much of the code is covered by tests)

<strong>Below you can see some screenshots taken while running the application</strong>:

![First Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%201.png)
<p align="center"><strong>Image 1</strong> - main window of the application</p>
<hr>

![Second Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%202.png)
<p align="center"><strong>Image 2</strong> - selecting a cell from the table (the details of the selected item will be displayed in the inputs (line edits controls))</p>
<hr>

![Third Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%203.png)
<p align="center"><strong>Image 3</strong> - selecting an item from the list (a new window containing the product's details is opened and also, the details will be displayed in the line edits (inputs))</p>
<hr>

![Fourth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%204.png)
<p align="center"><strong>Image 4</strong> - filtering products from the list after the type (green items are the filtered products that have the type "produse lactate" introduced by the user)</p>
<hr>

![Fifth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%205.png)
<p align="center"><strong>Image 5</strong> - window that contains all the types existing in the virtual store and the number of products from each type</p>
<hr>

![Sixth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%206.png)
<p align="center"><strong>Image 6</strong> - histogram that displays the distribution of the types</p>
<hr>

![Seventh Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%207.png)
<p align="center"><strong>Image 7</strong> - generating 50 products for the shopping cart (by clicking the "Genereaza cos" button)</p>
<hr>

![Eigth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%208.png)
<p align="center"><strong>Image 8</strong> - window containing 50 random vertical and horizontal rectangles with random colors (one rectangle for each item/product from the shopping cart)</p>
<hr>

![Nineth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%209.png)
<p align="center"><strong>Image 9</strong> - selecting an item from the list containing the products from the shopping cart</p>
<hr>

![Tenth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2010.png)
<p align="center"><strong>Image 10</strong> - selecting a cell from the table containing the products from the shopping cart</p>
<hr>

![Eleventh Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2011.png)
<p align="center"><strong>Image 11</strong> - window that also displays the items from the shopping cart (selecting a cell from the table)</p>
<hr>

![Twelveth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2012.png)
<p align="center"><strong>Image 12</strong> - window that also displays the items from the shopping cart (selecting an item from the table)</p>
<hr>

![Thirteenth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2013.png)
<p align="center"><strong>Image 13</strong> - exporting the shopping cart to a CSV and HTML files (the name of the file will be "cumparaturi" + the extension of the file (.csv for CSV file and .html for the HTML file))</p>
<hr>

![Fourteenth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2014.png)
<p align="center"><strong>Image 14</strong> - confirmation message (message box) for closing the "Cos de cumparaturi" window</p>
<hr>

![Fiftheenth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2015.png)
<p align="center"><strong>Image 15</strong> - content of the "cumparaturi.csv" export file opened using Excel program (you can see all the products/items from the shopping cart and the quantity of each product)</p>
<hr>

![Sixteenth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2016.png)
<p align="center"><strong>Image 16</strong> - content of the "cumparaturi.html" export file opened using Google Chrome browser (you can see all the products/items from the shopping cart and the quantity of each product)</p>
<hr>

![Seventeenth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%2017.png)
<p align="center"><strong>Image 17</strong> - overview of the application (all existing windows)</p>
<hr>

<strong>TODO</strong>:
- remove item from shopping cart option
- save the shopping cart content in a text file (data persistence for the shopping cart)
- create database repository (add data persistence in a SQL database like MySQL or PostgreSQL) ✅
- redo operation (for operations on the products/items (for example redo add new item or redo delete/remove existing item))
