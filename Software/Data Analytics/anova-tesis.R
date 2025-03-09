#Carga de la tabla 
library(readxl)
Datos<- read_excel("anotaciones.xlsx",
                   sheet = "Hoja 2",
                   col_types = c("text", "text", "text", 
                                 "numeric", "numeric", "numeric",
                                 "numeric","numeric"))

#factorizacion de las temperaturas (niveles)
Datos$Tratamiento<-as.factor(Datos$Tratamiento)

#analisis descriptivo de los datos
summary(Datos)

#Descricion de medianas y desvio estandar de las variables respuesta 
#respecto de la variable tratamiento
aggregate(cbind(TdE,MFE,Tdeincubacion) ~ Tratamiento, data = Datos, FUN = mean)
aggregate(cbind(TdE,MFE,Tdeincubacion) ~ Tratamiento, data = Datos, FUN = sd)

aggregate(TdE ~ Temperatura, data = Datos, FUN = mean)
aggregate(TdE ~ Temperatura, data = Datos, FUN = sd)

aggregate(MFE ~ Temperatura, data = Datos, FUN = mean)
aggregate(MFE ~ Temperatura, data = Datos, FUN = sd)

aggregate(Tdeincubacion ~ Temperatura, data = Datos, FUN = mean)
aggregate(Tdeincubacion ~ Temperatura, data = Datos, FUN = sd)

#graficos de la interaccion entre las variables respuestas y la var. tratamiento
library(ggplot2)
plot(Datos)

ggplot(data = Datos, 
       aes(x = Tratamiento, y = TdE, color = Tratamiento)) +
  geom_boxplot() +
  ggtitle("Tasa de eclosión respecto de los Tratamientos de incubación.")+
  theme_bw()
ggplot(data = Datos, 
       aes(x = Tratamiento, y = MFE, color = Tratamiento)) +
  geom_boxplot() +
  ggtitle("Malformaciones fisicas evidentes respecto de los Tratamiento de incubación.")+
  theme_bw()

ggplot(data = Datos, 
       aes(x = Tratamiento, y = Tdeincubacion, color = Tratamiento)) +
  geom_boxplot() +
  ggtitle("Tiempo de incubación respecto de los Tratamiento de incubación.")+
  theme_bw()

ggplot(data = Datos, aes(x = MFE, y = TdE, colour = Tratamiento,
                         group = Tratamiento)) +
  stat_summary(fun = mean, geom = "point") +
  stat_summary(fun = mean, geom = "line") +
  ggtitle("Malformaciones físicas evidentes respecto de la 
Tasa de eclosión, discriminados por las 
temperaturas de incubación.")+
  theme_bw()

ggplot(data = Datos, aes(x = Tdeincubacion, y = TdE, colour = Tratamiento,
                         group = Tratamiento)) +
  stat_summary(fun = mean, geom = "point") +
  stat_summary(fun = mean, geom = "line") +
  ggtitle("Tasa de eclosión respecto de los Tiempos de incubación,
 discriminado por los Tratamientos.")+
  theme_bw()
ggplot(data = Datos, aes(x = Tdeincubacion, y = MFE, colour = Tratamiento,
                         group = Tratamiento)) +
  stat_summary(fun = mean, geom = "point") +
  stat_summary(fun = mean, geom = "line") +
  ggtitle("Malformaciones físicas evidentes respecto de los
Tiempos de incubación, discriminados por los Tratamientos.")+
  theme_bw()
ggplot(data = Datos, aes(x = Tratamiento, y = `Alevin nadador (Horas)`, 
                         colour = `Variedad del lote`,
                         group = `Variedad del lote`)) +
  stat_summary(fun = mean, geom = "point") +
  stat_summary(fun = mean, geom = "line") +
  ggtitle("Tiempo de incubación respecto del temperatura para el 
desarollo de alevines nadadores, discriminado por la variedad.")+
  theme_bw()

ggplot(data = Datos, aes(x = Tratamiento, y = `Aparicion de ojo y/o vertebras (Horas)`, 
                         colour = `Variedad del lote`,
                         group = `Variedad del lote`)) +
  stat_summary(fun = mean, geom = "point") +
  stat_summary(fun = mean, geom = "line") +
  ggtitle("Tiempo de incubación respecto del temperatura en el desarollo
de ojos y columna vertebral en huevos, discriminado por la variedad.")+
  theme_bw()
library(scatterplot3d)
scatterplot3d(Datos$Tratamiento,Datos$TdE,Datos$Tdeincubacion,angle=27,
              type="h",highlight.3d=FALSE,pch= 19,color = "red", axis = TRUE,
              xlab="Tratamiento",
              ylab="TdE",
              zlim = (0:400),
              ylim = (0:90),
              zlab="Temienpo de incubación (horas)",cex.lab=1.2,
              main = "Tiempo de incubación en función de los Tratamientos,
respecto de la Tasas de eclosión (TdE).") 

scatterplot3d(Datos$Tratamiento,Datos$MFE,Datos$Tdeincubacion,angle=27,
              type="h",highlight.3d=FALSE,pch= 19,color = "blue",
              xlab="Tratamiento",
              ylab="MFE",
              zlim = (0:400),
              ylim = (0:100),
              zlab="Temienpo de incubacion (horas)",cex.lab=1.2,
              main = "Tiempo de incubación en función de los Tratamientos, 
respecto de las Malformaciones físicas evidentes (MFE).") 

#Eliminacion del nivel "6" por ser un valor costante y unico.
Datos<-Datos[c(-1,-8,-15),]

#Testeo de normalidad de las variables respuesta
#Tasa de eclosion respecto de la temperatura
#shapiro.test(Datos$TdE[Datos$Temperatura == "T1"])
shapiro.test(Datos$TdE[Datos$Temperatura == "T2"])
shapiro.test(Datos$TdE[Datos$Temperatura == "T3"])
shapiro.test(Datos$TdE[Datos$Temperatura == "T4"])
shapiro.test(Datos$TdE[Datos$Temperatura == "T5"])
shapiro.test(Datos$TdE[Datos$Temperatura == "T6"])
shapiro.test(Datos$TdE[Datos$Temperatura == "T7"])

#Malformacion fisica evidente respecto de la temperatura
#shapiro.test(Datos$MFE[Datos$Temperatura == "6"])
shapiro.test(Datos$MFE[Datos$Temperatura == "T2"])
shapiro.test(Datos$MFE[Datos$Temperatura == "T3"])
shapiro.test(Datos$MFE[Datos$Temperatura == "T4"])
shapiro.test(Datos$MFE[Datos$Temperatura == "T5"])
shapiro.test(Datos$MFE[Datos$Temperatura == "T6"])
shapiro.test(Datos$MFE[Datos$Temperatura == "T7"])

#Tiemo de incuvacion respecto de la temperatura
#shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "6"])
shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "T2"])
shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "T3"])
shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "T4"])
shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "T5"])
shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "T6"])
shapiro.test(Datos$Tdeincubacion[Datos$Temperatura == "T7"])

#test de homogeneidad de varianza 
fligner.test(TdE ~ Temperatura,Datos)
fligner.test(MFE ~ Temperatura,Datos)
fligner.test(Tdeincubacion ~ Temperatura,Datos)

library(carData)
library(car)
leveneTest(TdE ~ Temperatura,Datos,center = "median")
leveneTest(MFE ~ Temperatura,Datos,center = "median")
leveneTest(Tdeincubacion ~ Temperatura,Datos,center = "median")

#Test de ANOVA de una sola via
anova1 <- aov(Datos$TdE ~ Datos$Tratamiento)
summary(anova1)
anova2 <- aov(Datos$MFE ~ Datos$Tratamiento)
summary(anova2)
anova3 <-aov(Datos$Tdeincubacion ~ Datos$Tratamiento)
summary(anova3)
anovamultiple<-aov(Datos$TdE+Datos$MFE+Datos$Tdeincubacion ~ Datos$Tratamiento)
summary(anovamultiple)

#Comparacion multiples, contrastes POST_HOC
#comparcion multiple bonferroni (Tdeincubacion)
pairwise.t.test(x = Datos$Tdeincubacion, g = Datos$Tratamiento, 
                p.adjust.method = "bonferroni",
                pool.sd = TRUE, paired = FALSE, alternative = "two.sided")

#comparcion multiple bonferroni (TdE)
pairwise.t.test(Datos$TdE,Datos$Tratamiento, p.adjust.method = "bonferroni",
                pool.sd = TRUE, paired = FALSE, alternative = "two.sided")

#comparcion multiple bonferroni (MFE)
pairwise.t.test(x = Datos$MFE, g = Datos$Tratamiento,
                p.adjust.method = "bonferroni",
                pool.sd = TRUE, paired = FALSE, alternative = "two.sided")



#comparcion multiple Tukey (Tdeincubacion)
#anova1= TdE~temperatura
TukeyHSD(anova1)
plot(TukeyHSD(anova1))

#anova2= MFE~temperatura
TukeyHSD(anova2)
plot(TukeyHSD(anova2))

#anova3= TdEincubacion~temperatura
TukeyHSD(anova3)
plot(TukeyHSD(anova3))

#anovamultiple = TdE+MFE+Tdeincubacion ~ Temperatura
TukeyHSD(anovamultiple)
plot(TukeyHSD(anovamultiple))

#Tamaño del efecto del n^2
library(lsr)
etaSquared(anova1)
etaSquared(anova2)
etaSquared(anova3)

#Potencia del ANOVA 
library(stats)
power.anova.test(groups = 6, n = 18,
                 between.var = 1, within.var = 3,
                 sig.level = 0.05)

