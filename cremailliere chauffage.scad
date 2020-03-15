//!OpenSCAD


//--------------------------------------
//
//      Definition des variables
//
//--------------------------------------
affiche_cage = true;
affiche_cremailliere = true;
affiche_pignon = true;
affiche_corps_cage = true;
affiche_couvercle_cage = true;
nb_dents_cremailliere = 15;
nb_dents_pignon = 8;


//--------------------------------------
//
//      module principal
//
//--------------------------------------
union(){
  if (affiche_cremailliere) {
    rotate([90, 90, 0]){
      translate([-10, -62, -52.5]){
        cremaillere(nb_dents_cremailliere);
      }
    }
  }

  if (affiche_pignon) {
    rotate([0, 0, 0]){
      translate([0, 0, 0]){
        pignon(nb_dents_pignon);
      }
    }
  }

  if (affiche_cage) {
    cage();
  }

}

//--------------------------------------
//
//      module cremailliere
//
//--------------------------------------
module cremaillere(nb_dents) {
  union(){
    for (i = [1 : abs(1) : nb_dents]) {
      Dent(i);
    }

    translate([0, 8, -5]){
      rotate([90, 0, 90]){
        difference() {
          cylinder(r1=15, r2=15, h=10, center=false);

          cylinder(r1=3, r2=3, h=10, center=false);
        }
      }
    }
  }
}


//--------------------------------------
//
//      module pignon
//
//--------------------------------------
module pignon(nb_dents) {
  union(){
    union(){
      difference() {
        union(){
          cylinder(r1=30, r2=30, h=10, center=false);
          translate([0, 0, -10]){
            cylinder(r1=10, r2=10, h=30, center=false);
          }
        }

        translate([0, 0, -20]){
          cylinder(r1=5, r2=5, h=40, center=false);
        }
      }
      translate([3, -5, -10]){
        cube([5, 10, 30], center=false);
      }
      translate([-8, -5, -10]){
        cube([5, 10, 30], center=false);
      }
    }
    for (k = [1 : abs(1) : nb_dents]) {
      rotate([0, 0, (k * (360 / nb_dents))]){
        translate([15, 15, 10]){
          rotate([0, 90, 0]){
            Dent(0);
          }
        }
      }
    }

  }
}

//--------------------------------------
//
//      module cage
//
//--------------------------------------
module cage() {
  union(){
    if (affiche_corps_cage) {
      translate([-70, -25, 11]){
        difference() {
          union(){
            difference() {
              cube([125, 50, 10], center=false);

              translate([70, 25, 0]){
                cylinder(r1=10.5, r2=10.5, h=10, center=false);
              }
            }
            translate([115, 0, -11]){
              cube([10, 50, 15], center=false);
            }
            translate([0, 0, -11]){
              cube([10, 50, 15], center=false);
            }
            translate([125, 12.5, 0]){
              difference() {
                cube([15, 25, 10], center=false);

                translate([8, 12.5, 0]){
                  cylinder(r1=3, r2=3, h=10, center=false);
                }
              }
            }
            translate([-15, 12.5, 0]){
              difference() {
                cube([15, 25, 10], center=false);

                translate([8, 12.5, 0]){
                  cylinder(r1=3, r2=3, h=10, center=false);
                }
              }
            }
          }

          translate([120, 40, -40]){
            cylinder(r1=1, r2=1, h=40, center=false);
          }
          translate([120, 10, -40]){
            cylinder(r1=1, r2=1, h=40, center=false);
          }
          translate([5, 40, -40]){
            cylinder(r1=1, r2=1, h=40, center=false);
          }
          translate([5, 10, -40]){
            cylinder(r1=1, r2=1, h=40, center=false);
          }
        }
      }
    }

    if (affiche_couvercle_cage) {
      couvercle_cage();
    }

  }
}



//--------------------------------------
//
//      module couvercle cage
//
//--------------------------------------
module couvercle_cage() {
  translate([-70, -25, -11]){
    difference() {
      cube([125, 50, 10], center=false);

      translate([70, 25, 0]){
        cylinder(r1=10.5, r2=10.5, h=10, center=false);
      }
      translate([5, 10, 0]){
        cylinder(r1=2, r2=2, h=10, center=false);
      }
      translate([5, 40, 0]){
        cylinder(r1=2, r2=2, h=10, center=false);
      }
      translate([120, 10, 0]){
        cylinder(r1=2, r2=2, h=10, center=false);
      }
      translate([120, 40, 0]){
        cylinder(r1=2, r2=2, h=10, center=false);
      }
      translate([52.5, 25, 0]){
        cylinder(r1=3, r2=3, h=10, center=false);
      }
      translate([52.5, 25, 0]){
        cylinder(r1=5, r2=5, h=5, center=false);
      }
      translate([87.5, 25, 0]){
        cylinder(r1=3, r2=3, h=10, center=false);
      }
      translate([87.5, 25, 0]){
        cylinder(r1=5, r2=5, h=5, center=false);
      }
    }
  }
}


//--------------------------------------
//
//      module dent
//
//--------------------------------------
module Dent(numero) {
  translate([0, 0, (numero * 25)]){
    union(){
      translate([0, 0, -25]){
        linear_extrude( height=10, twist=0, scale=[1, 3], center=false){
          square([10, 10], center=false);
        }
      }
      translate([0, 0, -15]){
        cube([10, 30, 5], center=false);
      }
      mirror([0,0,1]){
        linear_extrude( height=10, twist=0, scale=[1, 3], center=false){
          square([10, 10], center=false);
        }
      }
    }
  }
}

