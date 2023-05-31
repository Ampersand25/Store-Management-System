console.log("Welcome to script.js!");

function getNumberOfRows(table) {
    return table.rows.length;
}

function getNumberOfCols(table) {
    return table.rows[0].cells.length;
}

function compare(val1, val2, asc) {
    return (asc) ? (val1 <= val2) : (val1 >= val2);
}

function swapCells(table, row1, col1, row2, col2) {
    const temp = table.rows[row1].cells[col1].innerHTML;
    table.rows[row1].cells[col1].innerHTML = table.rows[row2].cells[col2].innerHTML;
    table.rows[row2].cells[col2].innerHTML = temp;
}

function isNumber(str) {
    return !isNaN(str);
}

function sortVerticalTable(table, totalRows, totalCols, rowIndex, asc) {
    console.log("\n");
    console.log((asc) ? ("*SORT ASCENDING*") : ("*SORT DESCENDING*"));

    for(let col1 = 1; col1 < totalCols; ++col1) {
        for(let col2 = col1 + 1; col2 < totalCols; ++col2) {
            const leftTableCellValue = table.rows[rowIndex].cells[col1].innerHTML;
            const rightTableCellValue = table.rows[rowIndex].cells[col2].innerHTML;

            let comp;
            if(isNumber(leftTableCellValue) && isNumber(rightTableCellValue)) {
                const leftTableCellValueToNumber = Number(leftTableCellValue);
                const rightTableCellValueToNumber = Number(rightTableCellValue);
                comp = compare(leftTableCellValueToNumber, rightTableCellValueToNumber, asc);
            }
            else {
                comp = compare(leftTableCellValue, rightTableCellValue, asc);
            }

            if(!comp) {
                for (let row = 0; row < totalRows; ++row) {
                    swapCells(table, row, col1, row, col2);
                }
            }
        }
    }
}

function sortHorizontalTable(table, totalRows, totalCols, colIndex, asc) {
    console.log("\n");
    console.log((asc) ? ("*SORT ASCENDING*") : ("*SORT DESCENDING*"));

    for(let row1 = 1; row1 < totalRows; ++row1) {
        for(let row2 = row1 + 1; row2 < totalRows; ++row2) {
            const upTableCellValue = table.rows[row1].cells[colIndex].innerHTML;
            const downTableCellValue = table.rows[row2].cells[colIndex].innerHTML;

            let comp;
            if(isNumber(upTableCellValue) && isNumber(downTableCellValue)) {
                const upTableCellValueToNumber = Number(upTableCellValue);
                const downTableCellValueToNumber = Number(downTableCellValue);
                comp = compare(upTableCellValueToNumber, downTableCellValueToNumber, asc);
            }
            else {
                comp = compare(upTableCellValue, downTableCellValue, asc);
            }

            if(!comp) {
                for (let col = 0; col < totalCols; ++col) {
                    swapCells(table, row1, col, row2, col);
                }
            }
        }
    }
}

function sortTable(table, totalRows, totalCols, rowIndex, colIndex, asc, isVertical) {
    (isVertical) ? (sortVerticalTable(table, totalRows, totalCols, rowIndex, asc)) : (sortHorizontalTable(table, totalRows, totalCols, colIndex, asc));
}

function createSortableTable(table, isVertical) {
    const totalRows = getNumberOfRows(table);
    const totalCols = getNumberOfCols(table);

    console.log("\n");
    console.log(`Number of rows: ${totalRows}`);
    console.log(`Number of cols: ${totalCols}`);

    let lastHeaderText = "";
    let asc = true;

    document.addEventListener("DOMContentLoaded", function() {
        const headers = table.getElementsByTagName("th");
        for(let i = 0; i < headers.length; ++i) {
            headers[i].addEventListener("click", function() {
                const headerText = this.textContent;
                const rowIndex = this.parentNode.rowIndex;
                const colIndex = Array.prototype.indexOf.call(this.parentNode.children, this);

                console.log("\n");
                console.log("Header clicked");
                console.log(`Text: ${headerText}`);
                console.log(`Row: ${rowIndex}`);
                console.log(`Col: ${colIndex}`);

                asc = headerText !== lastHeaderText ? true : !asc;
                sortTable(table, totalRows, totalCols, rowIndex, colIndex, asc, isVertical);

                lastHeaderText = headerText;
            });
        }
    });
}

function createHorizontalSortableTables() {
    const verticalTables = document.getElementsByClassName("vertical-table");
    for(let i = 0; i < verticalTables.length; ++i) {
        createSortableTable(verticalTables.item(i), true);
    }
}

function createVerticalSortableTables() {
    const horizontalTables = document.getElementsByClassName("horizontal-table");
    for(let i = 0; i < horizontalTables.length; ++i) {
        createSortableTable(horizontalTables.item(i), false);
    }
}

function main() {
    createHorizontalSortableTables();
    createVerticalSortableTables();
}

main();