import { useEffect, useState } from "react";
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, ResponsiveContainer } from "recharts";
import { motion } from "framer-motion";


const SalesOverviewChart = ({salesData}) => {
	
	// Formatear los datos para que se ajusten a los requerimientos de recharts
	const formattedData = [];
	if (salesData.length !== 0) {
		for (let i = 0; i < salesData.length; i++) {
			const item = salesData[i];
			formattedData.push({
				name: item.month.slice(5, 7), // Extraer los últimos 2 caracteres (el mes)
				sales: item.total_por_mes
			});
		}
	}

	return (
		<motion.div
			className='bg-gray-800 bg-opacity-50 backdrop-blur-md shadow-lg rounded-xl p-6 border border-gray-700'
			initial={{ opacity: 0, y: 20 }}
			animate={{ opacity: 1, y: 0 }}
			transition={{ delay: 0.2 }}
		>
			<h2 className='text-lg font-medium mb-4 text-gray-100'>Sales Overview: 2023 - 2024</h2>

			<div className='h-80'>
				<ResponsiveContainer width={"100%"} height={"100%"}>
					<LineChart data={formattedData}>
						<CartesianGrid strokeDasharray='3 3' stroke='#4B5563' />
						{/* <XAxis dataKey={"name"} stroke='#9ca3af' /> */}
						<XAxis 
							dataKey="name" 
							stroke="#9ca3af" 
							tick={{ fill: "#9ca3af" }} 
							label={{ value: "Mes", position: "insideBottomRight", offset: 0 }} 
						/>
						{/* <YAxis stroke='#9ca3af' /> */}
						<YAxis 
							stroke="#9ca3af" 
							tick={{ fill: "#9ca3af" }} 
							label={{ value: "Ventas", angle: -90, position: "insideLeft" }} 
						/>
						<Tooltip
							contentStyle={{
								backgroundColor: "rgba(31, 41, 55, 0.8)",
								borderColor: "#4B5563",
							}}
							itemStyle={{ color: "#E5E7EB" }}
						/>
						<Line
							type='monotone'
							dataKey='sales'
							stroke='#6366F1'
							strokeWidth={3}
							dot={{ fill: "#6366F1", strokeWidth: 2, r: 6 }}
							activeDot={{ r: 8, strokeWidth: 2 }}
						/> 
					</LineChart>
				</ResponsiveContainer>
			</div>
		</motion.div>
	);
};
export default SalesOverviewChart;