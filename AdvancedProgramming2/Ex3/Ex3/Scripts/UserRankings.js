//add navigation bar
$(function () {
    if (sessionStorage.getItem("loggedInUser") === null) {
        $("#nav-placeholder").load("navigationbar.html");
    }
    else {
        $("#nav-placeholder").load("SignedNavBar.html");
    }
});

var UsersData = "../api/Registry";
$.getJSON(UsersData, function (data) {
    var i = 0;
    data.sort(function (x, y) {
        return ((y.Wins - y.Loses) - (x.Wins - x.Loses));
    });
    data.forEach(function (RegistryModel) {
        i++;
        $("#RankTbl").append("<tr><td>" +i+ "</td>"+"<td>" + RegistryModel.UserName + "</td>" +
            "<td>" + RegistryModel.Wins+ "</td>" +
            "<td>" + RegistryModel.Loses  + "</td></tr>");
    });
});