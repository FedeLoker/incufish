#graficos paper incufish
tabla<-read.table("clipboard",header=T,dec=",",sep="\t",encoding="latin1") 
str(tabla)
attach(tabla)

tabla$temperatura<-as.numeric(tabla$temperatura)
tabla$tiempo<-as.numeric(tabla$tiempo)

library(ggplot2)

grafica1 = ggplot(tabla,aes(tiempo,temperatura))

#grafica1

grafica1 + 
geom_point() + geom_smooth(method = "lm") + scale_y_continuous(limits = c(12,22)) + 
ggtitle("Rendimiento promedio de la Peltier a volumen
    de un litro sin contenido liquido por hora de trabajo")+
  theme(plot.title = element_text(hjust = 0.5))+
  theme(plot.title = element_text(face = "bold"))

####
boxplot(temperatura~tiempo, data = tabla)
####

tabla$tiempo<-as.factor(tabla$tiempo)
grafico2 = qplot(x = tiempo, y = temperatura, data = tabla, geom = "boxplot")
grafico2 + scale_y_continuous(limits = c(12,22))+ 
  ggtitle("Rendimiento promedio de la Peltier a volumen
    de un litro sin contenido liquido por hora de trabajo")+
  theme(plot.title = element_text(hjust = 0.5))+
  theme(plot.title = element_text(face = "bold"))
