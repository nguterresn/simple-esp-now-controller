## Simple ESPNow Controller

The following project description is a brief of the full explanation [here](https://www.nunonogueira.com/battlebutbot/2wd-bot).

![Top view of the controller](<../img/IMG_8857 – grande.jpeg>)

![Other view of the controller](<../img/IMG_8858 – grande.jpeg>)

### Hardware

The controller is battery (LiPo) powered and uses the [ESPNow](https://www.espressif.com/en/solutions/low-power-solutions/esp-now) wireless protocol as its communication protocol. Here is the list of components:

- A [ESP32 dev board](https://www.aliexpress.com/item/1005006336964908.html?spm=a2g0o.productlist.main.1.3ed4neKBneKBuG&algo_pvid=bad824ef-1169-4427-93c4-e35e6495c7ac&algo_exp_id=bad824ef-1169-4427-93c4-e35e6495c7ac-0&pdp_npi=4%40dis%21USD%2113.32%214.43%21%21%2195.86%2131.92%21%4021039cae17221643100751581e7a1b%2112000036806447869%21sea%21SE%21939121189%21&curPageLogUid=vA5i9RVmCyqr&utparam-url=scene%3Asearch%7Cquery_from%3A); The dev kit uses a [ESP32-WROOM-32 module](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf).
- Two [joystick](https://www.aliexpress.com/item/1005006403673836.html?spm=a2g0o.productlist.main.5.13895533RH6hXd&algo_pvid=7c5deec1-f07a-452f-878c-9248a4440e84&algo_exp_id=7c5deec1-f07a-452f-878c-9248a4440e84-2&pdp_npi=4%40dis%21USD%214.27%211.40%21%21%2130.74%2110.11%21%402103850917221644320492196ed5e6%2112000037042471248%21sea%21SE%21939121189%21&curPageLogUid=3gPkOW5tIeXQ&utparam-url=scene%3Asearch%7Cquery_from%3A) modules. They are not the best, however, the calibration can be done through software.
- One [TP4096 based charging module](https://www.aliexpress.com/item/1005006585278260.html?spm=a2g0o.productlist.main.1.530439e62hpvgp&algo_pvid=d599414f-9d6d-4a5a-a06f-3fcb7991e20d&algo_exp_id=d599414f-9d6d-4a5a-a06f-3fcb7991e20d-0&pdp_npi=4%40dis%21USD%2114.66%214.69%21%21%21105.44%2133.74%21%40210385db17221644581152944ef676%2112000037732397864%21sea%21SE%21939121189%21&curPageLogUid=VY6EvGKXgMx9&utparam-url=scene%3Asearch%7Cquery_from%3A), capable of charging 3.7V LiPo batteries.
- A [3.7V LiPo battery](https://www.aliexpress.com/item/1005007003031544.html?spm=a2g0o.productlist.main.21.51446849KCc4Tq&algo_pvid=2e2ab1a3-069e-4d1c-a6d1-bebc972702a6&algo_exp_id=2e2ab1a3-069e-4d1c-a6d1-bebc972702a6-10&pdp_npi=4%40dis%21USD%213.48%212.09%21%21%2125.00%2115.00%21%4021039c5917221645201446424e4eb1%2112000039014942184%21sea%21SE%21939121189%21X&curPageLogUid=9bYJEoW8DnMN&utparam-url=scene%3Asearch%7Cquery_from%3A) with 1200mAh capacity. One with a different capacity also fits.
- A [rocker switch](https://www.aliexpress.com/item/1005006117766211.html?spm=a2g0o.productlist.main.1.2a507ddb2D30Jg&algo_pvid=6204abff-ae91-4de2-bd82-a9d678efb9cb&algo_exp_id=6204abff-ae91-4de2-bd82-a9d678efb9cb-0&pdp_npi=4%40dis%21USD%214.61%212.31%21%21%2133.13%2116.56%21%402103853f17221645880518141e6109%2112000035829578264%21sea%21SE%21939121189%21X&curPageLogUid=RgutVUHJ11iZ&utparam-url=scene%3Asearch%7Cquery_from%3A) to turn ON/OFF the controller.

### Software

As stated previously, the joysticks are not the _best_. Their read analog voltage, from both axis, differs from one to another. To mitigate the diference, I've introduced a `CALIBRATION_DELTA`.

I've also mapped the read analog voltage from 0 until 4096 to -100 until 100. The mapped values help materialize the value of each read value into a 2 axis (X and Y) graph, but they are not necessarly mandatory for the end goal.

### Design

The enclosure to glue everything together is a 12cm x 9cm PLA printed design with a border radius of 2cm.

![Final Design](../img/IMG_8859.jpeg)

That's all folks! Have safe drives ;)
