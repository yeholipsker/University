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
    this.rows = ko.observable("").extend({ required: { message: "Please enter number of columns" }, number: true });
    this.columns = ko.observable("").extend({ required: { message: "Please enter number of columns" }, number: true });
    this.Algos = ko.observable(["Bfs", "Dfs"]);
    this.selectedAlgo = ko.observable("");
    this.set = function () {
        localStorage.selctedAlgo = ko.toJS(that.selectedAlgo);
        localStorage.rows = ko.toJS(that.rows);
        localStorage.columns = ko.toJS(that.columns);

    };
    this.isFormValid = ko.computed(function () {

        return this.columns.isValid() && this.rows.isValid();
    }, this);
}


ko.applyBindings(new AppViewModel(), document.getElementById("settings"));