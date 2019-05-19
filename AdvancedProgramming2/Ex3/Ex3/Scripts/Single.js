//add navigation bar
$(function () {
    if (sessionStorage.getItem("loggedInUser") === null) {
        $("#nav-placeholder").load("navigationbar.html");
    }
    else {
        $("#nav-placeholder").load("SignedNavBar.html");
    }
});
ko.validation.registerExtenders();
function AppViewModel() {
    var that = this;
    this.Name = ko.observable("").extend({ required: { message: "please enter The Game's Name" } });
    this.rows = ko.observable("").extend({ required: { message: "Please enter number of rows" }, number: true });
    this.columns = ko.observable("").extend({ required: { message: "Please enter number of columns" }, number: true });
    this.algoOptions = ko.observable(["Bfs", "Dfs"]);
    this.selectedAlgo = ko.observable("");
    this.StartBtn = function () {

        var apiUrl = "../api/Single/" + that.Name() + "/" + that.rows() + "/" + that.columns();
    $.ajax({
        method: "GET",
        url: apiUrl
    }).done(function (maze) {

        var krows = maze.Rows;
        var cols = maze.Cols;   
        var startRow = maze.Start.Row;
        var startCol = maze.Start.Col;
        var exitRow = maze.End.Row;
        var exitCol = maze.End.Col;

        var mazeData = new Array(krows);
        for (var i = 0; i < krows; i++) {
            mazeData[i] = new Array(cols);
        }

        var fromStr = maze.Maze.split("");

        for (var j = 0; j < krows; j++) {
            for (var k = 0; k < cols; k++) {
                mazeData[j][k] = fromStr[(j * cols) + k];
            }
        }

        var mazeBoard = $("#mazeCanvas").mazeBoard(mazeData, startRow, startCol, exitRow, exitCol,true);
        document.title = $("#mazeName").val();

    });
    };
    this.SlvBtn = function () {

        if (that.selectedAlgo() == "Bfs") {
            algo = 1;
        } else {
            algo = 0;
        }
        var apiUrl = "../api/Single/" + that.Name() + "/" + algo;
        $.getJSON(apiUrl).done(function (solution) {
            var fromSolution = solution.Solution.split("");
            $("#mazeCanvas").solveMaze(fromSolution);
        });
    };

   

    this.isFormValid = ko.computed(function () {

        return this.columns.isValid() && this.rows.isValid(), this.Name.isValid();
    }, this);
}
ko.applyBindings(new AppViewModel(),document.getElementById("single"));

/*});*/
//{"Name":"my","Maze":"0001001110000101101000000","Rows":5,"Cols":5,"Start":{"Row":0,"Col":2},"End":{"Row":2,"Col":2}}