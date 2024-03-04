#pip install simplekml

import simplekml
kml = simplekml.Kml()
#kml.newpoint(name="Ciutadella", coords=[(3.838603,40.001289,100)])  # lon, lat, optional height
linestring = kml.newlinestring(name="Cansat1", 
                               description="Trajectòria cansat")

39.992930, 3.837368
linestring.coords = [(3.837439,39.992767,0), 
                     (3.837368,39.992930,25),
                     ( 3.836913, 39.992865,50),
                     (3.836629,39.992799,75)
                    ]
linestring.altitudemode = simplekml.AltitudeMode.absolute #relativetoground
linestring.style.linestyle.width = 3
linestring.style.linestyle.color = simplekml.Color.red
linestring.extrude = 1
#linestring.polystyle.fill = 0
linestring.polystyle.color = simplekml.Color.hexa("ff000050")
linestring.linestyle.gxlabelvisibility = 1

kml.save("test.kml")