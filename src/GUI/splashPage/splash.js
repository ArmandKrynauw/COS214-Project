$(document).ready(function () {
  let battlesUrl = "battlesList.json";
  let promise = new Promise(function (resolve, reject) {
    $.getJSON(battlesUrl, (json) => {
      resolve(json);
    }).then((battles) => {
      battles.forEach((battle) => {
        let battleName = battle.name;
        let country1IMG = battle.country1;
        let country2IMG = battle.country2;
        $("<button></button>", {
          id: battleName,
          type: "button",
          class: "list-group-item list-group-item-action text-center",
          html: `<div class="warInfo">
                          <img
                          class="flagImage"
                          src="images/${country1IMG}"
                          alt=""
                          width="450px"
                          height="450px"
                          />
                          <div class="warName">${battleName}</div>
                          <img
                          class="flagImage"
                          src="images/${country2IMG}"
                          alt=""
                          width="450px"
                          height="450px"
                          />
                      </div>`,
        }).appendTo(".list-group");
      });
    });
  });
});
