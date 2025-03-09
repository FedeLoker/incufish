library(dplyr)
library(readxl)
Datalogger1 <- read_excel("C:/Users/Home/Downloads/Datalogger1.xlsx", 
                          sheet = "Hoja 1", col_types = c("numeric", 
                                                          "text", "text", "numeric", "numeric", 
                                                          "text"))
Datos<-Datalogger1
a0<-summary(Datos)
print(a0)
Sys.sleep(2)
readline("si desea avanzar oprima <enter> en caso contrario <control + c>")

library(ggplot2)

#Tab2022<-filter(Datos, Fechas == 2022)
#str(Tab2022)

pdf("plot.pdf")

grafico<- ggplot(data=Datos, 
      aes(x=Incuvadora, y=Valor, color= Incuvadora))

grafico+geom_point()+ 
      geom_line()+
      scale_color_manual(name = "Incubadoras", values = c("red", "blue", "green", "purple"))+
      ggtitle("Desempeño de las incuvadoras en los tres periodos, entre el año 2022 y 2023.")+
      theme(plot.title = element_text(color="Black", face="bold", size=10, hjust=0.5))+
      scale_y_continuous(breaks = seq(2,26,2))+
      labs(x="Incubadoras",y="Temperaturas en grados Centigrados")+
      theme(axis.title = element_text(color="Black", face="bold", size=8))+
      theme(legend.title = element_text(colour = "Black", face = "bold", size = 12))+
  theme(legend.position = "bottom")
      

dev.off()

Tab2023<-filter(Datos, Fechas == 2023) 
str(Tab2023)
pdf("plot2023.pdf")

ggplot(data=Tab2023, 
      aes(x=Incuvadora, y=Valor, color= Incuvadora))+
      geom_point()+ 
      geom_line()+
      ylim(5,25)+
      scale_color_manual(name = "Incubadoras", values = c("red", "blue", "green", "purple"))+
      ggtitle("         Desempeño de las incuvadoras periodo 
  del 30 de enero al 10 de febrero del 2023, variedad Cometa")+
      theme(plot.title = element_text(color="Black", face="bold", size=10, hjust=0.35))+
      labs(x="Incubadoras",y="Temperaturas en grados Centigrados")+
      theme(axis.title = element_text(color="Black", face="bold", size=10))

  
dev.off()

readline("si desea avanzar oprima <enter> en caso contrario <control + c>")

print("Incuvadora a 6°C")
I01<-filter(Tab2022, Tempset == 6, Fechas == 2022)

a1<-summary(I01)
print(a1)
a2<-mean(I01$Valor)
print("media")
print(a2)
a3<-sd(I01$Valor)
print("desvio estandar")
print(a3)
print("resultados de Incu1-6°C")
Sys.sleep(2)

print("Incuvadora a 12°C")
I02<-filter(Tab2022, Tempset == 12, Fechas == 2022)

b1<-summary(I02)
print(b1)
print("media")
b2<-mean(I02$Valor)
print(b2)
print("desvio estandar")
b3<-sd(I02$Valor)
print(b3)
print("resultados de Incu2-12°C")
Sys.sleep(2)

print("Incuvadora a 18°C")
I03<-filter(Tab2022, Tempset == 18, Fechas == 2022)

c1<-summary(I03)
print(c1)
print("media")
c2<-mean(I03$Valor)
print(c2)
print("desvio estandar")
c3<-sd(I03$Valor)
print(c3)
print("resultados de Incu3-18°C")
Sys.sleep(2)

print("Incuvadora a 24°C")
I04<-filter(Tab2022, Tempset == 24, Fechas == 2022)

d1<-summary(I04)
print(d1)
print("media")
d2<-mean(I04$Valor)
print(d2)
print("desvio estandar")
d3<-sd(I04$Valor)
print(d3)
print("resultados de Incu4-24°C")


print("Incuvadora a 6°C")
I01<-filter(Tab2023, Tempset == 6, Fechas == 2023)

a1<-summary(I01)
print(a1)
print("media")
a2<-mean(I01$Valor)
print(a2)
print("desvio estandar")
a3<-sd(I01$Valor)
print(a3)
print("resultados de Incu1-6°C")
Sys.sleep(2)

print("Incuvadora a 12°C")
I02<-filter(Tab2023, Tempset == 12, Fechas == 2023)

b1<-summary(I02)
print(b1)
print("media")
b2<-mean(I02$Valor)
print(b2)
print("desvio estandar")
b3<-sd(I02$Valor)
print(b3)
print("resultados de Incu2-12°C")
Sys.sleep(2)

print("Incuvadora a 18°C")
I03<-filter(Tab2023, Tempset == 18, Fechas == 2023)

c1<-summary(I03)
print(c1)
print("media")
c2<-mean(I03$Valor)
print(c2)
print("desvio estandar")
c3<-sd(I03$Valor)
print(c3)
print("resultados de Incu3-18°C")
Sys.sleep(2)

print("Incuvadora a 24°C")
I04<-filter(Tab2023, Tempset == 24, Fechas == 2023)

d1<-summary(I04)
print(d1)
print("media")
d2<-mean(I04$Valor)
print(d2)
print("desvio estandar")
d3<-sd(I04$Valor)
print(d3)
print("resultados de Incu4-24°C")
