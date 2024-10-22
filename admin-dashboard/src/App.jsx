import { Route, Routes, useLocation } from "react-router-dom"
import OverviewPage from "./pages/OverviewPage"
import ProductsPage from "./pages/ProductsPage"
import Sidebar from "./components/Sidebar"
import ClientsPage from "./pages/ClientsPage"
import AddClientForm from "./components/clients/AddClientForm"
import SalesPage from "./pages/SalesPage"
import AddSaleForm from "./components/sales/AddSaleForm"

function App() {
  const location = useLocation();

  const showBlurBackground = location.pathname !== "/agregar-cliente"; // Sin blur en agregar-cliente

  return (
    <div className='flex h-screen bg-gray-900 text-gray-100 overflow-hidden'>

      {/* Background */}
      {showBlurBackground && (
        <div className="fixed inset-0 z-0">
          <div className="absolute inset-0 bg-gradient-to-br from-gray-900 via-gray-800 to-gray-900 opacity-80" />
          <div className="absolute inset-0 backdrop-blur-sm" />
        </div>
      )}

      <Sidebar />
      <Routes>
        <Route path='/' element={<OverviewPage />} />
        <Route path='/products' element={<ProductsPage />} />
        <Route path='/clients' element={<ClientsPage />} />
        <Route path="/agregar-cliente" element={<AddClientForm />} />
        <Route path="/sales" element={<SalesPage />} />
        <Route path="/nueva-venta" element={<AddSaleForm />} />
      </Routes>
    </div>
  )
}

export default App
