type recipe = {
  .
  "id": string,
  "authorId": string,
  "collaborators": Js.Dict.t(Js.boolean),
  "isPrivate": Js.boolean,
  "title": string,
  "description": string,
  "titleSearch": Js.Dict.t(Js.boolean),
  "created": float,
  "updated": float,
  "imageUrl": Js.null(string),
  "tags": Js.Dict.t(Js.boolean),
  "source": Js.null(string),
  "instructions": string
};

module Recipe = {
  let name = "recipes";
  type t = recipe;
  let blank: (string, string) => recipe =
    (id, authorId) => {
      let now = Js.Date.now();
      let empty = Js.Dict.empty();
      {
        "id": id,
        "authorId": authorId,
        "collaborators": empty,
        "isPrivate": Js.Boolean.to_js_boolean(false),
        "title": "",
        "description": "",
        "titleSearch": empty,
        "created": now,
        "updated": now,
        "imageUrl": Js.null,
        "tags": empty,
        "source": Js.null,
        "instructions": ""
      }
    };
};