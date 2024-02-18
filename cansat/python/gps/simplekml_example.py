#pip install simplekml

import simplekml
kml = simplekml.Kml()
#kml.newpoint(name="Ciutadella", coords=[(3.838603,40.001289,100)])  # lon, lat, optional height
linestring = kml.newlinestring(name="Cansat1", 
                               description="Trajectòria cansat")

linestring.coords = [(3.838603,40.001289,100,0), 
                    (3.831694,39.999645,50)
                    ]
linestring.altitudemode = simplekml.AltitudeMode.absolute #relativetoground
linestring.style.linestyle.width = 3
linestring.style.linestyle.color = simplekml.Color.red
linestring.extrude = 1
#linestring.polystyle.fill = 0
linestring.polystyle.color = simplekml.Color.hexa("ff000050")
linestring.linestyle.gxlabelvisibility = 1

kml.save("ciutadella.kml")