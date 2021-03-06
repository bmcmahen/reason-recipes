// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Curry        = require("bs-platform/lib/js/curry.js");
var Js_primitive = require("bs-platform/lib/js/js_primitive.js");

var Storage = /* module */[];

function optMap(fn, value) {
  if (value) {
    return /* Some */[Curry._1(fn, value[0])];
  } else {
    return /* None */0;
  }
}

function fsUid(fs) {
  return optMap((function (prim) {
                return prim.uid;
              }), Js_primitive.null_undefined_to_opt(fs.app.auth().currentUser));
}

var Auth = /* module */[/* fsUid */fsUid];

function Collection(Config) {
  var get = function (fb) {
    return fb.collection(Config[/* name */0]);
  };
  return /* module */[/* get */get];
}

var Query = /* module */[];

exports.Storage    = Storage;
exports.optMap     = optMap;
exports.Auth       = Auth;
exports.Collection = Collection;
exports.Query      = Query;
/* No side effect */
