# Store-Management-System
<strong>Icons used in the application (except "happyIcon" and "sadIcon") are from Flaticon (link: https://www.flaticon.com/) and are absolute free</strong>:
- histogramIcon: <a href="https://www.flaticon.com/free-icons/histogram" title="histogram icons">Histogram icons created by Freepik - Flaticon</a>
- itemShoppingCartIcon: <a href="https://www.flaticon.com/free-icons/item" title="item icons">Item icons created by berkahicon - Flaticon</a>
- percentageHistogramIcon: <a href="https://www.flaticon.com/free-icons/interest" title="interest icons">Interest icons created by Freepik - Flaticon</a>
- productIcon: <a href="https://www.flaticon.com/free-icons/box" title="box icons">Box icons created by Freepik - Flaticon</a>
- shoppingCartIcon: <a href="https://www.flaticon.com/free-icons/shopping-cart" title="shopping cart icons">Shopping cart icons created by Freepik - Flaticon</a>
- shoppingCRUDIcon: <a href="https://www.flaticon.com/free-icons/add-product" title="add product icons">Add product icons created by Smashicons - Flaticon</a>
- shoppingReadOnlyIcon: <a href="https://www.flaticon.com/free-icons/groceries" title="groceries icons">Groceries icons created by justicon - Flaticon</a>
- storeIcon: <a href="https://www.flaticon.com/free-icons/shop" title="shop icons">Shop icons created by Freepik - Flaticon</a>
- typesIcon: <a href="https://www.flaticon.com/free-icons/skincare" title="skincare icons">Skincare icons created by Flat-icons-com - Flaticon</a>

<hr>

<strong>Description</strong>:
- Qt Widgets Application for Windows (desktop app) that manages the items (products) of a virtual store
- the app has a layered architecture: presentation layer (UI and GUI), business layer (service), infrastructure layer (repositories), validation layer (validators for the entities) and domain layer (entities from the domain of the problem)
- data (products/items from the store) can be stored/saved in memory, in a text file or in a MySQL database
- saving data in a database works for both debug and release configurations (but release configuration is recommended)
- shopping cart is not persistent (is only saved in memory)
- the app was developed in Visual Sudio 2022 Community IDE using C++ and QT Framework (version 6.5.0)
- the app contains the following Qt modules: Qt Core, Qt GUI and Qt Widgets
- configuration was set to debug when creating the app
- platform is x64
- "Info tipuri" button is not enabled (is disabled) when saving the products/items in a database, which means that both "Tipuri produse" and "Histograma tipuri produse" windows will be unavailable

<hr>

<strong>The design patterns used in developing the application are</strong>:
- Observer (also known as publish-subscribe). For example the windows that displays the content of the shopping cart are all observers/subscribers and the shopping cart is the observable/publisher, which means that the a new item is added or removed from the shopping cart, all the windows that are related to the shopping cart will display the new content of the shopping cart that the user has created (each modification/update of the shopping cart will result in the windows being notified about the changes)
- Model View (Qt version of MVC (Model View Controller)). The application uses models for all the lists and tables (each list is a QListView and each table is a QTableView and both have a model)

<hr>

<strong>The application has the following features</strong>:
- CRUD operations on the products/items from the store: an user can add a new product/item, can update the type and/or price of an existing product/item (note: when a product is updated/modified then all the items/products with the same name and producer from the shopping cart will be updated aswell by changing their type and price to the new values provided by the user (store admin)), can delete an existing product/item (note: when an item is removed/deleted from the virtual store's catalog then all the items/products with the same name and producer will be removed from the shopping cart (if there are any)) and can search for a specific product/item
- undo operation: the user can undo the last operation that was executed (for example if the last operation was delete/remove, if the user chooses to undo it, then the deleted/removed product/item will be added back in the store). The undo operation is not persistent (is not saved in a file or in a database) but can be called multiple times (if an item is added, then the same item is updated and then the same item is removed from the store, the user can call undo for 3 times: first the item will be added back in the store (undo for remove/delete operation), then the same item will be updated to its first state (undo for update operation) and after that the item will be removed from the store (undo for add operation))
- redo operation: the user can redo the last undo operation(s). Like undo, redo is not persistent (if the application is closed and open again then the redo will be unavailable for the current instance of the app)
- sorting products: the user can sort the existing products after name, type, name + type (if two products have the same name then they will be sorted according to their type), price and producer. The sorting can be both ascending and descending
- filtering the existing items from the virtual store: the user can filter all the items that have a specific name, specific type, specific price, or specific producer (filtering after name, type and producer is not case sensitive (it is case insensitive)). When filtering by price, there is the possibility to filter all the items that have a price less than a value, equal to a value, or greater than a value. The list will display items that match the applied filter in green, while items that don't match will be displayed in red. The table will only show the items that have been filtered
- selecting an item from the list: if the user selects an item from the list then a message box, containing the details about the selected product (name, type, price and producer), will be displayed
- adding a new product to the shopping cart: the user can add an existing product from the store's catalogue to the shopping cart (buy list)
- removing/deleting an existing item/product from the shopping cart
- generating items/products for the shopping cart: the user can randomly generate a number (between 1 and 100) of products for its shopping cart
- emptying the shopping cart: the user can empty the whole shopping cart by removing all the products (items) from it (the shopping cart will become empty after this operation)
- search for an item/product in the shopping cart and finding out how many products with a specific name/type/price/producer exists in the shopping cart (the user can search after one of the following options: name, type, price and producer)
- exporting the shopping cart: the user can export the content of the shopping cart to a CSV (Comma-Separated Values) or/and an HTML (HyperText Markup Language) file. The name of the file(s) must be given by the user. The exporting file(s) will be created inside the project directory in the folder named "Export cos cumparaturi". For opening CSV files, it is recommended to use Excel, and for opening HTML files, it is recommended to use a web browser such as Google Chrome. However, both types of files can also be opened using a text editor such as Notepad or Notepad++
- selecting an item from the shopping cart list: if the user selects an item from the shopping cart then a message box, containing the details about the selected product (name, type, price and producer), will be displayed

<hr>

<strong>Shortcuts available for buttons (QPushButton elements)</strong>:
- "Adauga produs in cos" (from main window): CTRL + A
- "Sterge continut cos" (from main window) : CTRL + S
- "Genereaza cos" (from main window)       : CTRL + G
- "CosCRUDGUI" (from main window)          : CTRL + C
- "CosReadOnlyGUI" (from main window)      : CTRL + R
- "Cumparaturi" (from main window)         : CTRL + M
- "Sortare" (from main window)             : ALT + S
- "Filtrare" (from main window)            : ALT + F
- "Adaugare" (from main window)            : ALT + A
- "Modificare" (from main window)          : ALT + M
- "Stergere" (from main window)            : ALT + T
- "Cautare" (from main window)             : ALT + C
- "Afisare" (from main window)             : ALT + E
- "Info tipuri" (from main window)         : ALT + I
- "Undo" (from main window)                : ALT + U
- "Redo" (from main window)                : ALT + R
- "Debug" (from main window)               : ALT + D
- "Clear" (from main window)               : ALT + L
- "Exit" (from main window)                : ALT + X
- "Generare cos de cumparaturi" (from "Fereastra CosCRUDGUI" window): ALT + G
- "Golire cos de cumparaturi" (from "Fereastra CosCRUDGUI" window)  : ALT + O
- "Adaugare" (from "Cos de cumparaturi" window)      : CTRL + D
- "Stergere" (from "Cos de cumparaturi" window)      : CTRL + Q
- "Golire" (from "Cos de cumparaturi" window)        : CTRL + O
- "Tiparire" (from "Cos de cumparaturi" window)      : CTRL + T
- "Generare" (from "Cos de cumparaturi" window)      : CTRL + N
- "Cautare in cos" (from "Cos de cumparaturi" window): CTRL + U
- "Export" (from "Cos de cumparaturi" window)        : CTRL + E
- "Clear" (from "Cos de cumparaturi" window)         : CTRL + L
- "Close" (from "Cos de cumparaturi" window)         : CTRL + X

<em>Observation: all buttons have different shortcuts!</em>

<hr>

<strong>While developing the app I also worked with tools such as</strong>:
- memory leak detector (for detecting memory leaks)
- debugger (for fixing bugs)
- CPU profiler from Diagnostic Tools (which measures the performance of the application (the app is recommended to be set to Release mode and not Debug, so that it can benefit from all possible optimizations))
- OpenCppCoverage (for seeing how much of the code is covered by tests)

<hr>

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
<p align="center"><strong>Image 5</strong> - window that contains all the types existing in the virtual store and the number of products from each type (window will not be available if the data is stored in the MySQL database)</p>
<hr>

![Sixth Screenshot](https://github.com/Ampersand25/Store-Management-System/blob/main/Screenshots/Screenshot%206.png)
<p align="center"><strong>Image 6</strong> - histogram that displays the distribution of the types (window will not be available if the data is stored in the MySQL database)</p>
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
- remove/delete option for an existing item from the shopping cart ✅
- save the shopping cart content/list in a text file (data persistence for the shopping cart in CSV (Comma-Separated Values) file) ✅
- create database repository (add data persistence in a SQL (Structured Query Language) database like MySQL or PostgreSQL) ✅
- redo operation (for undo operations) ✅
- add tooltips for different graphical elements ✅
- create a new histogram that displays the percentage for each type that exists in the virtual store's catalog. The histogram should represent the distribution of different types of items/products in the catalog, with each type represented by a horizontal bar, and the width of each bar indicating the percentage of that type in the catalog ✅
- solve the dangling pointers problem: if the data (items/products) is saved/stored in a MySQL database, then search will create a dangling pointer for each call (because in search function/method from repository the address of the searched products (if found) is returned (should return a copy instead)) ✅
- make the table from HTML (HyperText Markup Language) export file (table which contains the products/items from the shopping cart (buy list)) sortable (so that the lines/rows/records can be sorted ascending/descending after the values from one of the columns (on user clicks on a header, the records from the table will be sorted ascending/descending after the values from that column (that contains the header))) ✅
- search a product from the shopping cart's list after name, type, price or producer (the total number of products with the provided name/type/price/producer should be displayed in a message box (QMessageBox element)) ✅
- update the screenshots after all the new features are implemented (the application is in its final version)
