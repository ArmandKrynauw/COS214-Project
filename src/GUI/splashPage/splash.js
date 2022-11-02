$(document).ready(function () {
  //ajax call to get the data from the server
  $.ajax({
    url: "battlesList.json",
    type: "POST",
    dataType: "json",
    success: function (data) {
      console.log(data);
    },
    error: function (xhr, status, error) {
      alert("Error: " + error);
    },
  });
});
